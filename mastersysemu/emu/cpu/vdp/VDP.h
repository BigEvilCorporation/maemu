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
				void DrawLine(std::vector<u32>& data, int line);

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
					CTRL_VRAM_MASK	= 0x3FFF,
					CTRL_CRAM_MASK	= 0x001F,
					CTRL_HI_REG_MASK= 0x0F
				};

				struct ControlRegister
				{
					union
					{
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