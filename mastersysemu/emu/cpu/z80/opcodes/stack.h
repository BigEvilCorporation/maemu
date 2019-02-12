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
				enum RegisterDecode_Stack_16Bit
				{
					REGISTER_DECODE_STACK_16_REG_SHIFT = 0x4,
				};

				//Push 16-bit register to stack
				static u16 PUSH_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_16_MASK << REGISTER_DECODE_STACK_16_REG_SHIFT))
					{
					case (REGISTER_DECODE_16_BC << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.bc;
						break;
					case (REGISTER_DECODE_16_DE << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.de;
						break;
					case (REGISTER_DECODE_16_HL << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.hl;
						break;
					case (REGISTER_DECODE_16_AF << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.af;
						break;
					}

					//Decrement stack
					regs.sp--;

					//Push register
					bus.memoryController.WriteMemory(regs.sp, (*reg) >> 8);
					bus.memoryController.WriteMemory(regs.sp, (*reg) & 0xFF);

					return 0;
				}

				//Pop 16-bit register from stack
				static u16 POP_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_16_MASK << REGISTER_DECODE_STACK_16_REG_SHIFT))
					{
					case (REGISTER_DECODE_16_BC << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.bc;
						break;
					case (REGISTER_DECODE_16_DE << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.de;
						break;
					case (REGISTER_DECODE_16_HL << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.hl;
						break;
					case (REGISTER_DECODE_16_AF << REGISTER_DECODE_STACK_16_REG_SHIFT):
						reg = &regs.main.af;
						break;
					}

					//Decrement stack
					regs.sp--;

					//Pop register
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);

					(*reg) = (hi << 8) | lo;

					return 0;
				}
			}
		}
	}
}