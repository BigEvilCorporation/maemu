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
				static const int REGISTER_DECODE_CP_8_REG_SHIFT = 0x0;

				//Compare A with 8-bit register
				static u16 CP_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_CP_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_CP_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Compare A with reg
					u16 diff = (regs.main.a - (*reg));

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