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
				//Exchange AF with AF'
				static u16 EX_AF_AFa(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 temp = regs.main.af;
					regs.main.af = regs.alt.af;
					regs.alt.af = temp;

					return 0;
				}

				//Exchange BC with BC', DE with DE', HL with HL'
				static u16 EXX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 temp = regs.main.bc;
					regs.main.bc = regs.alt.bc;
					regs.alt.bc = temp;

					temp = regs.main.de;
					regs.main.de = regs.alt.de;
					regs.alt.de = temp;

					temp = regs.main.hl;
					regs.main.hl = regs.alt.hl;
					regs.alt.hl = temp;

					return 0;
				}
			}
		}
	}
}