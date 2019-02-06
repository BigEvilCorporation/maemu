#pragma once

#include "../Opcode.h"

#include <ion/core/debug/Debug.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static u16 NOP(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return 0;
				}

				static u16 Unknown(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					ion::debug::log << "Unknown opcode at " << regs.pc << ion::debug::end;
					return 0;
				}
			}
		}
	}
}