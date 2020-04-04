#pragma once

#include "../Opcode.h"
#include "../Interrupts.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				//Disable maskable interrupts
				static u16 DI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.internal.iff1 = 0;
					regs.internal.iff2 = 0;
					return opcode.cycles;
				}

				//Enable maskable interrupts
				static u16 EI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.internal.iff1 = 1;
					regs.internal.iff2 = 1;
					return opcode.cycles;
				}

				//Set interrupt mode 0
				static u16 IM_0(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.internal.im = Z80_INT_MODE0;
					return opcode.cycles;
				}

				//Set interrupt mode 1
				static u16 IM_1(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.internal.im = Z80_INT_MODE1;
					return opcode.cycles;
				}

				//Set interrupt mode 2
				static u16 IM_2(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.internal.im = Z80_INT_MODE2;
					return opcode.cycles;
				}

				//Return from interrupt
				static u16 RETI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//TODO
					return opcode.cycles;
				}

				//Return from non-maskable interrupt
				static u16 RETN(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//TODO
					return opcode.cycles;
				}
			}
		}
	}
}