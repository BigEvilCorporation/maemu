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
				static const int REGISTER_DECODE_INCDEC_8_REG_SHIFT = 0x3;
				static const int REGISTER_DECODE_INCDEC_16_REG_SHIFT = 0x4;

				//Increment 8-bit register
				static u16 INC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_INCDEC_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Increment reg
					(*reg)++;

					//Set flags
					ComputeFlagsZCS(*reg, regs.main.f);

					return 0;
				}

				//Decrement 8-bit register
				static u16 DEC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_INCDEC_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_INCDEC_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Decrement reg
					(*reg)--;

					//Set flags
					ComputeFlagsZCS(*reg, regs.main.f);

					return 0;
				}

				//Increment 16-bit register
				static u16 INC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_16_MASK << REGISTER_DECODE_INCDEC_16_REG_SHIFT))
					{
					case (REGISTER_DECODE_16_BC << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.bc;
						break;
					case (REGISTER_DECODE_16_DE << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.de;
						break;
					case (REGISTER_DECODE_16_HL << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.hl;
						break;
					case (REGISTER_DECODE_16_SP << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.sp;
						break;
					}

					//Increment reg
					(*reg)++;

					return 0;
				}

				//Decrement 16-bit register
				static u16 DEC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_16_MASK << REGISTER_DECODE_INCDEC_16_REG_SHIFT))
					{
					case (REGISTER_DECODE_16_BC << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.bc;
						break;
					case (REGISTER_DECODE_16_DE << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.de;
						break;
					case (REGISTER_DECODE_16_HL << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.main.hl;
						break;
					case (REGISTER_DECODE_16_SP << REGISTER_DECODE_INCDEC_16_REG_SHIFT):
						reg = &regs.sp;
						break;
					}

					//Decrement reg
					(*reg)--;

					return 0;
				}
			}
		}
	}
}