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

					return opcode.cycles;
				}

				//Jump to 8-bit relative offset
				static u16 JR_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Jump
					regs.pc += (s8)params[0];

					return opcode.cycles;
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

					return opcode.cycles;
				}

				//Jump to address in (HL)
				static u16 JP_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Jump to (HL)
					regs.pc = regs.main.hl;

					return opcode.cycles;
				}

				//Jump to address in (IX)
				static u16 JP_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Jump to (IX)
					regs.pc = regs.ix;

					return opcode.cycles;
				}

				//Jump to address in (IY)
				static u16 JP_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Jump to (IY)
					regs.pc = regs.iy;

					return opcode.cycles;
				}

				//Jump if Z set (to 8-bit relative offset)
				static u16 JR_Z_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z set
					if (regs.main.f & FLAG_Z)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return opcode.cycles;
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

					return opcode.cycles;
				}

				//Jump if C set (to 8-bit relative offset)
				static u16 JR_C_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If C set
					if (regs.main.f & FLAG_C)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return opcode.cycles;
				}

				//Jump if C not set (to 8-bit relative offset)
				static u16 JR_NC_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If C reset
					if ((regs.main.f & FLAG_C) == 0)
					{
						//Jump
						regs.pc += (s8)params[0];
					}

					return opcode.cycles;
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

					return opcode.cycles;
				}
			}
		}
	}
}