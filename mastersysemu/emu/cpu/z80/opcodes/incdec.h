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
				static const int REGISTER_DECODE_INCDEC_8_REG_SHIFT = 0x3;
				static const int REGISTER_DECODE_INCDEC_16_REG_SHIFT = 0x4;

				//Increment 8-bit register
				static u16 INC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Increment reg
					reg++;

					//Set flags
					ComputeFlagsZCS(reg, regs.main.f);

					return 0;
				}

				//Decrement 8-bit register
				static u16 DEC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_INCDEC_8_REG_SHIFT);

					//Decrement reg
					reg--;

					//Set flags
					ComputeFlagsZCS(reg, regs.main.f);

					return 0;
				}

				//Increment 16-bit register
				static u16 INC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_INCDEC_16_REG_SHIFT);

					//Increment reg
					reg++;

					return 0;
				}

				//Decrement 16-bit register
				static u16 DEC_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_INCDEC_16_REG_SHIFT);

					//Decrement reg
					reg--;

					return 0;
				}
			}
		}
	}
}