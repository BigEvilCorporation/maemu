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
				//Exchange AF with AF'
				static u16 EX_AF_AFa(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 temp = regs.main.af;
					regs.main.af = regs.alt.af;
					regs.alt.af = temp;

					return opcode.cycles;
				}

				//Exchange DE with HL
				static u16 EX_DE_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 temp = regs.main.de;
					regs.main.de = regs.main.hl;
					regs.main.hl = temp;

					return opcode.cycles;
				}

				//Exchange BC with BC', DE with DE', HL with HL'
				static u16 EXX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 temp = regs.main.bc;
					regs.main.bc = regs.alt.bc;
					regs.alt.bc = temp;

					temp = regs.main.de;
					regs.main.de = regs.alt.de;
					regs.alt.de = temp;

					temp = regs.main.hl;
					regs.main.hl = regs.alt.hl;
					regs.alt.hl = temp;

					return opcode.cycles;
				}

				//Exchange value at address in (SP) with HL
				static u16 EX_dSP_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 tempLo = bus.memoryController.ReadMemory(regs.sp);
					u8 tempHi = bus.memoryController.ReadMemory(regs.sp + 1);
					bus.memoryController.WriteMemory(regs.sp, regs.main.l);
					bus.memoryController.WriteMemory(regs.sp, regs.main.h);
					regs.main.l = tempLo;
					regs.main.h = tempHi;

					return opcode.cycles;
				}

				//Exchange value at address in (SP) with IX
				static u16 EX_dSP_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 tempLo = bus.memoryController.ReadMemory(regs.sp);
					u8 tempHi = bus.memoryController.ReadMemory(regs.sp + 1);
					bus.memoryController.WriteMemory(regs.sp, regs.ixl);
					bus.memoryController.WriteMemory(regs.sp, regs.ixh);
					regs.ixl = tempLo;
					regs.ixh = tempHi;

					return opcode.cycles;
				}

				//Exchange value at address in (SP) with IY
				static u16 EX_dSP_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 tempLo = bus.memoryController.ReadMemory(regs.sp);
					u8 tempHi = bus.memoryController.ReadMemory(regs.sp + 1);
					bus.memoryController.WriteMemory(regs.sp, regs.iyl);
					bus.memoryController.WriteMemory(regs.sp, regs.iyh);
					regs.iyl = tempLo;
					regs.iyh = tempHi;

					return opcode.cycles;
				}
			}
		}
	}
}