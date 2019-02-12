#pragma once

#include "../Opcode.h"
#include "SetFlags.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static const int REGISTER_DECODE_BIT_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_SET_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_SHIFT_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_OR_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_AND_8_REG_SHIFT = 0x0;

				static const int REGISTER_DECODE_BIT_MASK = 0x38;
				static const int REGISTER_DECODE_BIT_SHIFT = 0x03;

				//Set specified bit in an 8-bit register
				static u16 SET_b_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_OR_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Bit in first param
					*(reg) |= (1 << params[0]);
				}

				//Test specified bit on an 8-bit register
				static u16 BIT_b_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_OR_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Determine bit
					u8 bitIdx = (opcode.opcode & (REGISTER_DECODE_BIT_MASK << REGISTER_DECODE_BIT_SHIFT));

					//Set Z flag to bit
					SetFlagZ(((*reg) >> bitIdx) & 1, regs.main.f);

					return 0;
				}

				//Shift an 8-bit register to the left
				static u16 SLA_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_SHIFT_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_SHIFT_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Copy top bit to C flag
					SetFlagC((*reg) >> 7, regs.main.f);

					//Shift left
					(*reg) <<= 1;

					//Set Z/S flags
					ComputeFlagsZS(*reg, regs.main.f);

					return 0;
				}

				//Shift value at address in IX register + offset to the left
				static u16 SLA_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at (IX + offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Copy top bit to C flag
					SetFlagC(value >> 7, regs.main.f);

					//Shift left
					value <<= 1;

					//Set Z/S flags
					ComputeFlagsZS(value, regs.main.f);

					//Store value
					bus.memoryController.WriteMemory(regs.ix + params[0], value);

					return 0;
				}

				//Shift value at address in IY register + offset to the left
				static u16 SLA_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at (IY + offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Copy top bit to C flag
					SetFlagC(value >> 7, regs.main.f);

					//Shift left
					value <<= 1;

					//Set Z/S flags
					ComputeFlagsZS(value, regs.main.f);

					//Store value
					bus.memoryController.WriteMemory(regs.iy + params[0], value);
				}

				//Logic OR A with 8-bit register
				static u16 OR_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_OR_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_OR_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//OR A with reg
					regs.main.a |= (*reg);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with 8-bit register
				static u16 AND_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_AND_8_REG_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_AND_8_REG_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//AND A with reg
					regs.main.a &= (*reg);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with 8-bit literal
				static u16 AND_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with literal
					regs.main.a &= params[0];

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Invert A
				static u16 CPL_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.main.a = ~regs.main.a;

					return 0;
				}
			}
		}
	}
}