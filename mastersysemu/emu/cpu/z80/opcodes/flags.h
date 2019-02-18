#pragma once

#include "../Opcode.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				//Set the C flag
				static u16 SCF(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.main.f |= FLAG_C;

					return 0;
				}

				//Invert the C flag
				static u16 CCF(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.main.f ^= FLAG_C;

					return 0;
				}
			}
		}
	}
}