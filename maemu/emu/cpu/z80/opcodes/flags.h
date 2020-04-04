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
					//Set C
					SetFlagC(1, regs.main.f);
					SetFlagH(0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return opcode.cycles;
				}

				//Invert the C flag
				static u16 CCF(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy C to F, invert C
					SetFlagH((regs.main.f & FLAG_C) ? 1 : 0, regs.main.f);
					SetFlagC((regs.main.f & FLAG_C) ? 0 : 1, regs.main.f);
					SetFlagN(0, regs.main.f);

					return opcode.cycles;
				}
			}
		}
	}
}