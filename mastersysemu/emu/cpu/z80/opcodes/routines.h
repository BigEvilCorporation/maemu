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
				static const int REGISTER_DECODE_RST_CODE_MASK = 0x07;
				static const int REGISTER_DECODE_RST_CODE_SHIFT = 0x03;
				static const int REGISTER_DECODE_RST_CODE_TO_ADDR = 0x8;
				static const int REGISTER_DECODE_RET_CONDITION_SHIFT = 0x03;

				//Call routine at literal address
				static u16 CALL_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Push PC to stack
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, (regs.pc >> 8));
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, (regs.pc & 0xFF));

					//Load PC
					regs.pc = (params[1] << 8) | params[0];

					return 0;
				}

				//Return from routine to address at top of stack
				static u16 RET(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Pop PC from stack
					u8 lo = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;
					u8 hi = bus.memoryController.ReadMemory(regs.sp);
					regs.sp++;

					regs.pc = (hi << 8) | lo;

					return 0;
				}

				//Return on condition to address at top of stack
				static u16 RET_CC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine condition
					bool result = DecodeCondition(regs, opcode.opcode, REGISTER_DECODE_RET_CONDITION_SHIFT);

					//If condition met
					if (result)
					{
						//Pop PC from stack
						u8 lo = bus.memoryController.ReadMemory(regs.sp);
						regs.sp++;
						u8 hi = bus.memoryController.ReadMemory(regs.sp);
						regs.sp++;

						regs.pc = (hi << 8) | lo;
					}

					return 0;
				}

				//Call a restart routine
				static u16 RST(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get the address code
					u8 addrCode = (opcode.opcode >> REGISTER_DECODE_RST_CODE_SHIFT ) & REGISTER_DECODE_RST_CODE_MASK;

					//Convert to address
					u8 addrLo = addrCode * REGISTER_DECODE_RST_CODE_TO_ADDR;

					//Push PC to stack
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, (regs.pc >> 8));
					regs.sp--;
					bus.memoryController.WriteMemory(regs.sp, (regs.pc & 0xFF));

					//Set PC
					regs.pc = (u16)addrLo;

					return 0;
				}
			}
		}
	}
}