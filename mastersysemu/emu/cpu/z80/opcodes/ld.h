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
				//Load A from constant
				static u16 LD_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into A
					regs.main.a = params[0];

					return 0;
				}

				//Load B from constant
				static u16 LD_B(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into B
					regs.main.b = params[0];

					return 0;
				}

				//Load IX from constant
				static u16 LD_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into IX
					regs.ixh = params[0];
					regs.ixl = params[1];

					return 0;
				}

				//Load HL from constant
				static u16 LD_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into HL
					regs.main.h = params[0];
					regs.main.l = params[1];

					return 0;
				}

				//Load address in HL from constant
				static u16 LD_ADDR_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into (HL)
					bus.memoryController.WriteMemory(regs.main.hl, params[0]);

					return 0;
				}

				//Load A from value at address in HL
				static u16 LD_A_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read (HL)
					regs.main.a = bus.memoryController.ReadMemory(regs.main.hl);

					return 0;
				}
			}
		}
	}
}