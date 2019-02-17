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
				static const int REGISTER_DECODE_IO_8_REG_SHIFT = 0x3;

				//Write A to port at 8-bit address
				static u16 OUT_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Write A to port in param 1
					bus.portController.Write(params[0], regs.main.a);

					return 0;
				}

				//Write 8-bit register to port held in C
				static u16 OUT_C_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_IO_8_REG_SHIFT);

					//Write register to port in C
					bus.portController.Write(regs.main.c, reg);

					return 0;
				}

				//Read from port at 8-bit address to A
				static u16 IN_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read port in param 1 to A
					regs.main.a = bus.portController.Read(params[0]);

					return 0;
				}

				//Read from port at C into address at (HL), increment HL, decrement B
				static u16 INI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read from port in C
					u8 value = bus.portController.Read(regs.main.c);

					//Write to address at (HL)
					bus.memoryController.WriteMemory(regs.main.hl, value);

					//Increment HL, decrement B
					regs.main.hl++;
					regs.main.b--;

					//Set Z flag based on B
					ComputeFlagsZ(regs.main.b, regs.main.f);

					return 0;
				}

				//Write from (HL) to port and increment HL while B!=0
				static u16 OTIR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Write value at (HL) to port in C
					bus.portController.Write(regs.main.c, bus.memoryController.ReadMemory(regs.main.hl));

					//Increment HL
					regs.main.hl++;

					//Decrement B
					regs.main.b--;

					//If B != 0
					if (regs.main.b != 0)
					{
						//Reset PC to start of instruction (ED redirect + param = 2 bytes)
						regs.pc -= 2;
					}

					return 0;
				}
			}
		}
	}
}