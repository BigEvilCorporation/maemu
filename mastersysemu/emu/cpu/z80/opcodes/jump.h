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
				static const int REGISTER_DECODE_JP_CONDITION_SHIFT = 0x3;

				//Jump to literal 16-bit address
				static u16 JP_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Jump
					regs.pc = address;

					return 0;
				}

				//Jump to 8-bit relative offset
				static u16 JR_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Jump
					regs.pc += (s8)params[0];

					return 0;
				}

				//Jump on condition to literal address
				static u16 JP_CC_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine condition
					bool result = DecodeCondition(regs, opcode.opcode, REGISTER_DECODE_JP_CONDITION_SHIFT);

					//If condition met
					if (result)
					{
						//Load PC
						regs.pc = (params[1] << 8) | params[0];
					}

					return 0;
				}

				//Jump if Z set (to 8-bit relative offset)
				static u16 JR_Z_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z reset
					if (regs.main.f & FLAG_Z)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return 0;
				}

				//Jump if Z not set (to 8-bit relative offset)
				static u16 JR_NZ_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z reset
					if ((regs.main.f & FLAG_Z) == 0)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return 0;
				}

				//Decrement B, jump if non-zero (to 8-bit relative offset)
				static u16 DJNZ_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement B
					regs.main.b--;

					//If non-zero
					if (regs.main.b != 0)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return 0;
				}
			}
		}
	}
}