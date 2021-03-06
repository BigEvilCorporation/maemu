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
					u16& reg = DecodeReg16_Stack(regs, opcode.opcode, REGISTER_DECODE_STACK_16_REG_SHIFT);

					//Decrement stack and push register
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, reg >> 8);
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, reg & 0xFF);

					return opcode.cycles;
				}

				//Pop 16-bit register from stack
				static u16 POP_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16_Stack(regs, opcode.opcode, REGISTER_DECODE_STACK_16_REG_SHIFT);

					//Pop register and increment stack
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;

					reg = (hi << 8) | lo;

					return opcode.cycles;
				}

				//Push IX to stack
				static u16 PUSH_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement stack and push register
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, regs.ix >> 8);
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, regs.ix & 0xFF);

					return opcode.cycles;
				}

				//Pop IX from stack
				static u16 POP_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Pop register and increment stack
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;

					regs.ix = (hi << 8) | lo;

					return opcode.cycles;
				}

				//Push IY to stack
				static u16 PUSH_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Decrement stack and push register
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, regs.iy >> 8);
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, regs.iy & 0xFF);

					return opcode.cycles;
				}

				//Pop IY from stack
				static u16 POP_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Pop register and increment stack
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;

					regs.iy = (hi << 8) | lo;

					return opcode.cycles;
				}
			}
		}
	}
}