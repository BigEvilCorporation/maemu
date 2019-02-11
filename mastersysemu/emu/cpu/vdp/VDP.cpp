#include "VDP.h"
#include "Colour.h"
#include "../../Constants.h"

#include <functional>

#include <ion/core/memory/Memory.h>

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			VDP::VDP(Bus& bus)
				: m_bus(bus)
			{
				//Connect ports
				bus.portController.AddHandler(PORT_VDP_CTRL, std::bind(&VDP::ReadControl, this, std::placeholders::_1), std::bind(&VDP::WriteControl, this, std::placeholders::_1, std::placeholders::_2));
				bus.portController.AddHandler(PORT_VDP_DATA, std::bind(&VDP::ReadData, this, std::placeholders::_1), std::bind(&VDP::WriteData, this, std::placeholders::_1, std::placeholders::_2));
			}

			void VDP::Reset()
			{
				//TODO: Regs initial state
				for (int i = 0; i < VDP_NUM_REGISTERS; i++)
				{
					m_regs[i] = 0;
				}

				m_controlReg.word = 0;
				m_statusFlags = 0;
				m_hiByteLatch = false;
			}

			u8 VDP::ReadControl(u16 address)
			{
				//Reset byte latch
				m_hiByteLatch = false;

				//Control port read returns status byte
				return m_statusFlags;
			}

			u8 VDP::ReadData(u16 address)
			{
				//Reset byte latch
				m_hiByteLatch = false;

				//Data port read returns internal read buffer
				return m_readBuffer;
			}

			void VDP::WriteControl(u16 address, u8 value)
			{
				//Write byte to control reg
				if (m_hiByteLatch)
					m_controlReg.hi = value;
				else
					m_controlReg.lo = value;

				//If hi byte, check for immediate operations
				if (m_hiByteLatch)
				{
					if ((m_controlReg.word & CTRL_COMMAND_MASK) == CTRL_REG_WRITE)
					{
						//Write to register
						m_regs[m_controlReg.hi & CTRL_HI_REG_MASK] = m_controlReg.lo;
					}
					else if ((m_controlReg.word & CTRL_COMMAND_MASK) == CTRL_VRAM_READ)
					{
						//Read from VRAM to internal buffer
						m_readBuffer = m_bus.memoryControllerVRAM.ReadMemory(m_controlReg.word & CTRL_VRAM_MASK);

						//Increment address
						m_controlReg.word = ((m_controlReg.word + 1) & CTRL_VRAM_MASK);
					}
				}

				//Toggle hi/lo byte
				m_hiByteLatch = !m_hiByteLatch;
			}

			void VDP::WriteData(u16 address, u8 value)
			{
				//Write data
				if (((m_controlReg.word & CTRL_COMMAND_MASK) == CTRL_VRAM_WRITE)
					|| ((m_controlReg.word & CTRL_COMMAND_MASK) == CTRL_VRAM_READ))
				{
					//Write to VRAM
					m_bus.memoryControllerVRAM.WriteMemory(m_controlReg.word & CTRL_VRAM_MASK, value);

					//Write to internal buffer
					m_readBuffer = value;

					//Increment address (wrap around VRAM, preserve command bits)
					m_controlReg.word = (m_controlReg.word & CTRL_COMMAND_MASK) | ((m_controlReg.word + 1) & CTRL_VRAM_MASK);
				}
				else if ((m_controlReg.word & CTRL_COMMAND_MASK) == CTRL_CRAM_WRITE)
				{
					//Write to CRAM
					m_bus.memoryControllerCRAM.WriteMemory(m_controlReg.word & CTRL_CRAM_MASK, value);

					//Write to internal buffer
					m_readBuffer = value;

					//Increment address (wrap around VRAM, preserve command bits)
					m_controlReg.word = (m_controlReg.word & CTRL_COMMAND_MASK) | ((m_controlReg.word + 1) & CTRL_VRAM_MASK);
				}
				else
				{
					//TODO: Invalid write
				}

				//Reset byte latch
				m_hiByteLatch = false;
			}

			void VDP::DrawLine(u32* data, int line)
			{
				///////////////////////////////////////////////////////////////////
				//Get BG colour (from sprite palette)
				///////////////////////////////////////////////////////////////////

				u8 backdropIdx = m_regs[VDP_REG_7_BACKDROP_COLOUR] & 0xF;
				u8 backdropColour = m_bus.memoryControllerCRAM.ReadMemory(VDP_PALETTE_OFFS_SPRITE + backdropIdx);
				u32 backdropColourRGBA = ColourToRGB[backdropColour];

				///////////////////////////////////////////////////////////////////
				//BG plane
				///////////////////////////////////////////////////////////////////

				//Tile map address bits 13-11 are in bits 3-1 of register 2
				CellEntryAddress cellAddr;
				cellAddr.baseAddr = (m_regs[VDP_REG_2_NAME_TABLE_ADDR] & VDP_MAP_REG_ADDR_MASK) >> VDP_MAP_REG_ADDR_SHIFT;
				cellAddr.y = line / VDP_TILE_HEIGHT;

				CellEntry cell;

				for (int x = 0; x < VDP_SCREEN_WIDTH; x++)
				{
					//Compute cell word address
					cellAddr.x = x / VDP_TILE_WIDTH;

					//Read cell word
					cell.hi = m_bus.memoryControllerVRAM.ReadMemory(cellAddr.address);
					cell.lo = m_bus.memoryControllerVRAM.ReadMemory(cellAddr.address + 1);

					//Get tile address
					u16 tileAddr = cell.tileIdx * (VDP_TILE_WIDTH * VDP_TILE_HEIGHT / 2);

					//Offset by current line (4 bytes per line, wrapping around 8 lines per tile)
					u16 offsetY = (line & 0x7) * 4;

					//Read and combine bits from each bitplane
					u8 colourIdx = 0;
					u8 bitplaneShift = 8 - (x & 0x7);

					for (int i = 0; i < 4; i++)
					{
						//Read byte at x location
						u8 bitplaneByte = m_bus.memoryControllerVRAM.ReadMemory(tileAddr + offsetY + i);

						//Shift bitplane bit to LSB, back to top of nybble
						colourIdx |= ((bitplaneByte >> bitplaneShift) & 1) << 4;

						//Next bit
						colourIdx >>= 1;
					}

					//Fetch color from palette
					u16 colourAddr = cell.palette ? (colourIdx + VDP_PALETTE_OFFS_SPRITE) : colourIdx;
					u8 colour = m_bus.memoryControllerCRAM.ReadMemory(colourAddr);

					if (colour == 0)
					{
						//0 is transparent, write backdrop colour instead
						data[x] = backdropColourRGBA;
					}
					else
					{
						//Write RGB
						data[x] = ColourToRGB[colour];
					}
				}

				///////////////////////////////////////////////////////////////////
				//TODO: Sprite plane
				///////////////////////////////////////////////////////////////////
			}

			const Registers& VDP::GetRegisters() const
			{
				return m_regs;
			}
		}
	}
}