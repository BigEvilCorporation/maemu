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
				static const int REGISTER_DECODE_STACK_16_REG_SHIFT = 0x4;

				//Push 16-bit register to stack
				static u16 PUSH_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_STACK_16_REG_SHIFT);

					//Decrement stack and push register
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, reg >> 8);
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, reg & 0xFF);

					return 0;
				}

				//Pop 16-bit register from stack
				static u16 POP_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_STACK_16_REG_SHIFT);

					//Pop register and increment stack
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;

					reg = (hi << 8) | lo;

					return 0;
				}
			}
		}
	}
}