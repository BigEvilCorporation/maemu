#pragma once

#include "Constants.h"
#include "Registers.h"
#include "Bus.h"
#include "../../ports/PortController.h"

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			class VDP
			{
			public:
				VDP(Bus& bus);

				//Execution
				void Reset();

				//Ports
				u8 ReadControl(u16 address);
				u8 ReadData(u16 address);
				void WriteControl(u16 address, u8 value);
				void WriteData(u16 address, u8 value);

				//Rendering
				void DrawLine(u32* data, int line);

				//Debugging
				const Registers& GetRegisters() const;

			private:
				enum ControlBits
				{
					CTRL_VRAM_READ		= 0x0000,
					CTRL_VRAM_WRITE		= 0x4000,
					CTRL_REG_WRITE		= 0x8000,
					CTRL_CRAM_WRITE		= 0xC000,
				};

				enum AddressMasks
				{
					CTRL_COMMAND_MASK	= 0xC000,
					CTRL_VRAM_MASK		= 0x3FFF,
					CTRL_CRAM_MASK		= 0x001F,
					CTRL_HI_REG_MASK	= 0x0F
				};

				struct ControlRegister
				{
					union
					{
						struct
						{
							u8 lo;
							u8 hi;
						};

						u16 word;
					};
				};

				struct CellEntryAddress
				{
					//Cell word address:
					//
					//--bb byyy yyxx xxxw
					//---- -m-- ---- ---- 
					//b = map base address
					//y = row
					//x = column
					//w = hi/lo byte
					//m = mask bit (bit 0 of register $02)

					CellEntryAddress()
					{
						address = 0;
					}

					union
					{
						struct
						{
							u16 hiLoByte : 1;
							u16 x : 5;
							u16 y : 5;
							u16 baseAddr : 3;
							u16 unused : 2;
						};

						u16 address;
					};
				};
				
				struct CellEntry
				{
					//Cell word:
					//
					//---p cvhn nnnn nnnn
					//p = Priority
					//c = Palette
					//v = Vertical flip
					//h = Horizontal flip
					//n = Pattern index

					CellEntry()
					{
						word = 0;
					}

					union
					{
						struct
						{
							u16 tileIdx : 9;
							u16 flipX : 1;
							u16 flipY : 1;
							u16 palette : 1;
							u16 priority : 1;
							u16 unused : 3;
						};

						struct
						{
							u8 hi;
							u8 lo;
						};
						
						u16 word;
					};
				};

				Registers m_regs;
				Bus& m_bus;
				ControlRegister m_controlReg;

				bool m_hiByteLatch;
				u8 m_statusFlags;
				u8 m_readBuffer;
			};
		}
	}
}