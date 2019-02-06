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
				//Compare A with constant byte
				static u16 CP(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with byte in first param
					u16 diff = (regs.main.a - params[0]);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with A - essentially a nop
				static u16 CP_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return 0;
				}

				//Compare A with B
				static u16 CP_B(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with B
					u16 diff = (regs.main.a - regs.main.b);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with C
				static u16 CP_C(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with C
					u16 diff = (regs.main.a - regs.main.c);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with D
				static u16 CP_D(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with D
					u16 diff = (regs.main.a - regs.main.d);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with E
				static u16 CP_E(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with E
					u16 diff = (regs.main.a - regs.main.e);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with H
				static u16 CP_H(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with H
					u16 diff = (regs.main.a - regs.main.h);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with L
				static u16 CP_L(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with L
					u16 diff = (regs.main.a - regs.main.l);

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with value at address in HL
				static u16 CP_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with value at address in HL
					u16 diff = (regs.main.a - bus.memoryController.ReadMemory(regs.main.hl));

					//Set flags
					SetFlagsZCS(diff, regs.main.f);

					return 0;
				}
			}
		}
	}
}