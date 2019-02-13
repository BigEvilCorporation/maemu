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
				static const int REGISTER_DECODE_ARITH_REG_SHIFT = 0x3;

				//Subtract 8-bit literal from A
				static u16 SUB_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract literal from A
					regs.main.a -= params[0];

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract 8-bit register from A
				static u16 SUB_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;
					u8 regType = ((opcode.opcode >> REGISTER_DECODE_ARITH_REG_SHIFT) & REGISTER_DECODE_8_MASK);

					switch (regType)
					{
					case (REGISTER_DECODE_8_A):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L):
						reg = &regs.main.l;
						break;
					}

					//Subtract from A
					regs.main.a -= *reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}
			}
		}
	}
}