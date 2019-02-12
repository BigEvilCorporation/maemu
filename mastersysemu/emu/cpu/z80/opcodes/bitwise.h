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
				static const int REGISTER_DECODE_OR_8_REG_SHIFT = 0x0;

				//Logic OR A with 8-bit register
				static u16 OR_r(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_OR_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//OR A with reg
					regs.main.a |= (*reg);

					//Set flags
					SetFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Invert A
				static u16 CPL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.main.a = ~regs.main.a;

					return 0;
				}
			}
		}
	}
}