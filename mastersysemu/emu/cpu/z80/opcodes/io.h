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
			}
		}
	}
}