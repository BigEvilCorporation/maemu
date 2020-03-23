#pragma once

#include "../Opcode.h"

#include <ion/core/debug/Debug.h>
#include <ion/core/utils/STL.h>

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
					//Back to start of instruction
					regs.pc--;

					if (regs.internal.prefix1)
						regs.pc--;
					if (regs.internal.prefix2)
						regs.pc--;

					//Halt execution
					regs.internal.err = 1;

					//Unknown opcode
					std::stringstream err;
					err << "Unknown opcode [" << SSTREAM_HEX2(regs.internal.prefix1) << "] [" << SSTREAM_HEX2(regs.internal.prefix2) << "] (" << SSTREAM_HEX2(opcode.opcode) << ") at 0x" << SSTREAM_HEX4(regs.pc) << " - system halted";
					ion::debug::Log(err.str().c_str());

					return 0;
				}
			}
		}
	}
}