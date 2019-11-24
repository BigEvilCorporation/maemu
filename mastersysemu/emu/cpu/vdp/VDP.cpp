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
				bus.portController.AddHandler(SMS_PORT_VDP_CTRL, std::bind(&VDP::ReadControl, this, std::placeholders::_1), std::bind(&VDP::WriteControl, this, std::placeholders::_1, std::placeholders::_2));
				bus.portController.AddHandler(SMS_PORT_VDP_DATA, std::bind(&VDP::ReadData, this, std::placeholders::_1), std::bind(&VDP::WriteData, this, std::placeholders::_1, std::placeholders::_2));
				bus.portController.AddHandler(SMS_PORT_VDP_HCOUNTER, std::bind(&VDP::ReadHCounter, this, std::placeholders::_1), nullptr);
				bus.portController.AddHandler(SMS_PORT_VDP_VCOUNTER, std::bind(&VDP::ReadVCounter, this, std::placeholders::_1), nullptr);
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
				m_counterH = 0;
				m_counterV = 0;
			}

			u8 VDP::ReadControl(u16 address)
			{
				//Reset byte latch
				m_hiByteLatch = false;

				//Control port read returns status byte
				u8 status = m_statusFlags;

				//and clears vblank flag
				m_statusFlags &= ~VDP_STATUS_VBLANK;

				return status;
			}

			u8 VDP::ReadData(u16 address)
			{
				//Reset byte latch
				m_hiByteLatch = false;

				//Data port read returns internal read buffer
				return m_readBuffer;
			}

			u8 VDP::ReadHCounter(u16 address)
			{
				return m_counterH;
			}

			u8 VDP::ReadVCounter(u16 address)
			{
				return m_counterV;
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

			void VDP::BeginScanline(u16 scanline)
			{
				m_counterV = scanline;

				if (m_counterV == 0)
				{
					//Vertical interrupt
					m_statusFlags |= VDP_STATUS_VBLANK;
				}
			}

			u8 VDP::PeekStatus()
			{
				return m_statusFlags;
			}

			void VDP::DrawLine(u32* data, int scanline)
			{
				//Get BG colour (from sprite palette)
				u8 backdropIdx = m_regs[VDP_REG_7_BACKDROP_COLOUR] & 0xF;
				u8 backdropColour = m_bus.memoryControllerCRAM.ReadMemory(VDP_PALETTE_OFFS_SPRITE + backdropIdx);
				u32 backdropColourRGBA = ColourToRGB[backdropColour];

				bool screenActive = (m_regs[VDP_REG_1_MODE_CONTROL_2] & VDP_REG_SCREEN_ENABLE_MASK) != 0;

				if (!screenActive || (scanline < VDP_BORDER_TOP) || (scanline >= (VDP_SCANLINES_PAL - VDP_BORDER_BOTTOM)))
				{
					//Just draw BG colour
					for (int dstx = 0; dstx < VDP_SCREEN_WIDTH; dstx++)
					{
						data[dstx] = backdropColourRGBA;
					}
				}
				else
				{
					//Offset Y border
					u8 dsty = scanline - VDP_BORDER_TOP;

					//Get scroll values
					u8 scrollx = m_regs[VDP_REG_8_SCROLL_X];
					u8 scrolly = m_regs[VDP_REG_9_SCROLL_Y];
					u8 srcy = (dsty + scrolly) % (VDP_BG_PLANE_HEIGHT_TILES * VDP_TILE_HEIGHT);

					//Get sprite attribute table
					u16 spriteTableAddr = (m_regs[VDP_REG_5_SPRITE_ATTR_TABLE_ADDR] & VDP_SPRITE_REG_ADDR_MASK) << VDP_SPRITE_REG_ADDR_SHIFT;

					//Get sprite tiles bit 8
					u16 spriteTileIdxUpper = (m_regs[VDP_REG_6_SPRITE_PATTERN_TABLE_ADDR] & VDP_SPRITE_TILE_ADDR_MASK) << VDP_SPRITE_TILE_ADDR_SHIFT;

					//Get sprite size
					u8 spriteSizeIdx = (m_regs[VDP_REG_1_MODE_CONTROL_2] & VDP_SPRITE_SIZE_MASK) >> VDP_SPRITE_SIZE_SHIFT;
					u8 spriteWidth = 8;
					u8 spriteHeight = spriteSizeIdx ? 16 : 8;

					//Determine sprites on line
					Sprite spritesOnLine[VDP_SPRITES_MAX_PER_SCANLINE] = { 0 };
					u8 numSpritesOnLine = 0;

					for (int i = 0; i < VDP_SPRITES_MAX && numSpritesOnLine < VDP_SPRITES_MAX_PER_SCANLINE; i++)
					{
						//Fetch Y coord (+1)
						u8 ycoord = m_bus.memoryControllerVRAM.ReadMemory(spriteTableAddr + i) + 1;

						//If scanline within sprite
						if (dsty >= ycoord && dsty < (ycoord + spriteHeight))
						{
							//Offset to X coord/tile idx
							u16 tableXAddr = spriteTableAddr + (i * 2) + 0x80;

							//Add sprite to array
							Sprite& sprite = spritesOnLine[numSpritesOnLine++];
							sprite.y = ycoord;
							sprite.x = m_bus.memoryControllerVRAM.ReadMemory(tableXAddr);
							sprite.tileIdx = spriteTileIdxUpper | m_bus.memoryControllerVRAM.ReadMemory(tableXAddr + 1);

							//If double height sprites, ignore bottom bit
							if (spriteSizeIdx)
							{
								sprite.tileIdx &= 0xFFFE;
							}
						}
					}

					//Tile map address bits 13-11 are in bits 3-1 of register 2
					CellEntryAddress cellAddr;
					cellAddr.baseAddr = (m_regs[VDP_REG_2_NAME_TABLE_ADDR] & VDP_MAP_REG_ADDR_MASK) >> VDP_MAP_REG_ADDR_SHIFT;
					cellAddr.y = srcy / VDP_TILE_HEIGHT;

					CellEntry cell;

					//For each X pixel on line
					for (int dstx = 0; dstx < VDP_SCREEN_WIDTH; dstx++)
					{
						u8 colourIdx = 0;

						//If within X border
						if (dstx >= VDP_BORDER_LEFT && dstx < (VDP_SCREEN_WIDTH - VDP_BORDER_RIGHT))
						{
							//Find sprite first
							for (int i = 0; i < numSpritesOnLine && colourIdx == 0; i++)
							{
								//If x within sprite
								if (dstx >= spritesOnLine[i].x && dstx < (spritesOnLine[i].x + spriteWidth))
								{
									//Get x/y pixel within sprite
									u8 sprx = dstx - spritesOnLine[i].x;
									u8 spry = dsty - spritesOnLine[i].y;

									//Get tile index
									u16 tileIdx = spritesOnLine[i].tileIdx;

									//If double height, and in the lower half, use next tile
									if (spriteSizeIdx && spry >= 8)
									{
										tileIdx += 1;
									}

									//Get tile address
									u16 tileAddr = tileIdx * (VDP_TILE_WIDTH * VDP_TILE_HEIGHT / 2);

									//Read and combine bits from each bitplane
									u8 index = ReadBitPlaneColourIdx(tileAddr, sprx, spry, false, false);

									//If not transparent, use sprite pixel
									if (index > 0)
									{
										colourIdx = index + VDP_PALETTE_OFFS_SPRITE;
									}
								}
							}

							//If sprite not found or transparent, draw BG plane
							if (colourIdx == 0)
							{
								//Apply scroll
								u8 srcx = (dstx - scrollx) % (VDP_BG_PLANE_WIDTH_TILES * VDP_TILE_WIDTH);

								//Compute cell word address
								cellAddr.x = srcx / VDP_TILE_WIDTH;

								//Read cell word
								cell.hi = m_bus.memoryControllerVRAM.ReadMemory(cellAddr.address);
								cell.lo = m_bus.memoryControllerVRAM.ReadMemory(cellAddr.address + 1);

								//Get tile address
								u16 tileAddr = cell.tileIdx * (VDP_TILE_WIDTH * VDP_TILE_HEIGHT / 2);

								//Read and combine bits from each bitplane
								colourIdx = ReadBitPlaneColourIdx(tileAddr, srcx, srcy, cell.flipX, cell.flipY);

								//If using sprite palette, offset
								if (cell.palette)
								{
									colourIdx += VDP_PALETTE_OFFS_SPRITE;
								}
							}
						}

						if (colourIdx == 0)
						{
							//0 is transparent, write backdrop colour instead
							data[dstx] = backdropColourRGBA;
						}
						else
						{
							//Fetch color from palette
							u8 colour = m_bus.memoryControllerCRAM.ReadMemory((u16)colourIdx);

							//Write RGB
							data[dstx] = ColourToRGB[colour];
						}
					}
				}
			}

			u8 VDP::ReadBitPlaneColourIdx(u16 tileAddress, u8 x, u8 y, bool flipX, bool flipY)
			{
				//Offset by current line (4 bytes per line, wrapping around 8 lines per tile)
				u16 offsetY = (flipY ? (7 - (y & 0x7)) : (y & 0x7)) * 4;

				//Read and combine bits from each bitplane
				u8 colourIdx = 0;
				u8 bitplaneShift = flipX ? (x & 0x7) : (7 - (x & 0x7));

				for (int i = 0; i < 4; i++)
				{
					//Read byte at x location
					u8 bitplaneByte = m_bus.memoryControllerVRAM.ReadMemory(tileAddress + offsetY + i);

					//Shift bitplane bit to LSB, back to top of nybble
					colourIdx |= ((bitplaneByte >> bitplaneShift) & 1) << 4;

					//Next bit
					colourIdx >>= 1;
				}

				return colourIdx;
			}

			const Registers& VDP::GetRegisters() const
			{
				return m_regs;
			}
		}
	}
}