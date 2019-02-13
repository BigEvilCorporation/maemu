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
				static const int REGISTER_DECODE_CP_8_REG_SHIFT = 0x0;

				//Compare A with 8-bit register
				static u16 CP_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_CP_8_REG_SHIFT);

					//Compare A with reg
					u16 diff = (regs.main.a - reg);

					//Set flags
					ComputeFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with 8-bit literal
				static u16 CP_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with param
					u16 diff = (regs.main.a - params[0]);

					//Set flags
					ComputeFlagsZCS(diff, regs.main.f);

					return 0;
				}

				//Compare A with value at address in HL
				static u16 CP_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Compare A with value at address in HL
					u16 diff = (regs.main.a - bus.memoryController.ReadMemory(regs.main.hl));

					//Set flags
					ComputeFlagsZCS(diff, regs.main.f);

					return 0;
				}
			}
		}
	}
}