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
				//Halt execution until next interrupt
				static u16 HALT(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//TODO: Rewind PC until received interrupt
					return 0;
				}
			}
		}
	}
}