#pragma once

#include "../Opcode.h"
#include "SetFlags.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				//Increment A
				static u16 INC_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Increment A
					regs.main.a++;

					//Set flags
					SetFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Decrement A
				static u16 DEC_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement A
					regs.main.a--;

					//Set flags
					SetFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Increment B
				static u16 INC_B(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Increment B
					regs.main.b++;

					//Set flags
					SetFlagsZCS(regs.main.b, regs.main.f);

					return 0;
				}

				//Decrement B
				static u16 DEC_B(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement B
					regs.main.b--;

					//Set flags
					SetFlagsZCS(regs.main.b, regs.main.f);

					return 0;
				}

				//Increment HL
				static u16 INC_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Increment HL
					regs.main.hl++;

					return 0;
				}

				//Decrement HL
				static u16 DEC_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement HL
					regs.main.b--;

					return 0;
				}
			}
		}
	}
}