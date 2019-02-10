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
					if ((m_controlReg.word & CTRL_REG_WRITE) == CTRL_REG_WRITE)
					{
						//Write to register
						m_regs[m_controlReg.hi & CTRL_HI_REG_MASK] = m_controlReg.lo;
					}
					else if ((m_controlReg.word & CTRL_VRAM_READ) == CTRL_VRAM_READ)
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
				if (((m_controlReg.word & CTRL_VRAM_WRITE) == CTRL_VRAM_WRITE)
					|| ((m_controlReg.word & CTRL_VRAM_READ) == CTRL_VRAM_READ))
				{
					//Write to VRAM
					m_bus.memoryControllerVRAM.WriteMemory(m_controlReg.word & CTRL_VRAM_MASK, value);

					//Write to internal buffer
					m_readBuffer = value;

					//Increment address
					m_controlReg.word = ((m_controlReg.word + 1) & CTRL_VRAM_MASK);
				}
				else if ((m_controlReg.word & CTRL_CRAM_WRITE) == CTRL_CRAM_WRITE)
				{
					//Write to CRAM
					m_bus.memoryControllerCRAM.WriteMemory(m_controlReg.word & CTRL_CRAM_MASK, value);

					//Write to internal buffer
					m_readBuffer = value;

					//Increment address
					m_controlReg.word = ((m_controlReg.word + 1) & CTRL_VRAM_MASK);
				}
				else
				{
					//TODO: Invalid write
				}

				//Reset byte latch
				m_hiByteLatch = false;
			}

			void VDP::DrawLine(std::vector<u32>& data, int line)
			{
				//Initialise with BG colour (from sprite palette)
				u8 backdropIdx = m_regs[VDP_REG_7_BACKDROP_COLOUR] & 0xF;
				u8 backdropColour = m_bus.memoryControllerCRAM.ReadMemory(VDP_PALETTE_OFFS_SPRITE + backdropIdx);
				u32 backropColourRGBA = ColourToRGB[backdropColour];
				std::fill(data.begin(), data.end(), backropColourRGBA);

				//TODO: BG plane

				//TODO: Sprite plane
			}

			const Registers& VDP::GetRegisters() const
			{
				return m_regs;
			}
		}
	}
}