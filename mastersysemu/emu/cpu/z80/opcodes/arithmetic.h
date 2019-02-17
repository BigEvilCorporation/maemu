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
				static const int REGISTER_DECODE_ARITH_REG8_SHIFT = 0x3;
				static const int REGISTER_DECODE_ARITH_REG16_SHIFT = 0x4;

				//Add 8-bit literal to A
				static u16 ADD_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add param to A
					regs.main.a += params[0];

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add 16-bit register to HL
				static u16 ADD_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to HL
					regs.main.hl += reg;

					//Determine C/H flags
					ComputeFlagsHC(regs.main.hl, regs.main.f);

					return 0;
				}

				//Add 16-bit register to IX
				static u16 ADD_IX_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IX
					regs.ix += reg;

					//Determine C/H flags
					ComputeFlagsHC(regs.ix, regs.main.f);

					return 0;
				}

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
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					regs.main.a -= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}
			}
		}
	}
}