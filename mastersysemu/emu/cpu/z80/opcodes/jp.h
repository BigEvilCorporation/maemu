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
				//Jump to constant address
				static u16 JP_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Jump
					regs.pc = address;

					return 0;
				}

				//Jump if Z set
				static u16 JP_Z_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z set
					if (regs.main.f & FLAG_Z)
					{
						//Get address
						u16 address = (params[1] << 8) | params[0];

						//Jump
						regs.pc = address;
					}

					return 0;
				}

				//Jump if Z not set (to 16-bit literal)
				static u16 JP_NZ_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z reset
					if ((regs.main.f & FLAG_Z) == 0)
					{
						//Get address
						u16 address = (params[1] << 8) | params[0];

						//Jump
						regs.pc = address;
					}

					return 0;
				}

				//Jump if Z not set (offset by 8-bit literal)
				static u16 JR_NZ_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//If Z reset
					if ((regs.main.f & FLAG_Z) == 0)
					{
						//Get offset
						s8 offset = (s8)params[0];

						//Jump
						regs.pc += offset;
					}

					return 0;
				}
			}
		}
	}
}