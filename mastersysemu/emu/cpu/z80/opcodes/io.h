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
				//Write A to port at 8-bit address
				static u16 OUT_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Write A to port in param 1
					bus.portController.Write(params[0], regs.main.a);

					return 0;
				}

				//Write from (HL) to port and increment HL while B!=0
				static u16 OTIR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Write value at (HL) to port in C
					bus.portController.Write(regs.main.c, bus.memoryController.ReadMemory(regs.main.hl));

					//Increment HL
					regs.main.hl++;

					//Decrement B
					regs.main.b--;

					//If B != 0
					if (regs.main.b != 0)
					{
						//Reset PC to start of instruction (ED redirect + param = 2 bytes)
						regs.pc -= 2;
					}

					return 0;
				}
			}
		}
	}
}