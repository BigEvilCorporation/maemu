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
				enum RegisterDecode_LD_8Bit
				{
					REGISTER_DECODE_LD_8_REG1_SHIFT = 0x3,
					REGISTER_DECODE_LD_8_REG2_SHIFT = 0x0
				};

				enum RegisterDecode_LD_16Bit
				{
					REGISTER_DECODE_LD_16_REG1_SHIFT = 0x4,
				};

				//Load 8-bit register from literal
				static u16 LD_8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG1_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Load param
					(*reg) = params[0];

					return 0;
				}

				//Load 8-bit register from another 8-bit register
				static u16 LD_r_r(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine regs
					u8* reg1 = nullptr;
					u8* reg2 = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG1_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.l;
						break;
					}

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG2_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.main.l;
						break;
					}

					//Load
					(*reg1) = (*reg2);

					return 0;
				}

				//Load 8-bit register from IXH/IXL
				static u16 LD_r_r_DD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine regs
					u8* reg1 = nullptr;
					u8* reg2 = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG1_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg1 = &regs.main.l;
						break;
					}

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG2_SHIFT))
					{
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.ixh;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG2_SHIFT):
						reg2 = &regs.ixl;
						break;
					}

					//Load
					(*reg1) = (*reg2);

					return 0;
				}

				//Load 16-bit register from literal
				static u16 LD_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_16_MASK << REGISTER_DECODE_LD_16_REG1_SHIFT))
					{
					case (REGISTER_DECODE_16_BC << REGISTER_DECODE_LD_16_REG1_SHIFT):
						reg = &regs.main.bc;
						break;
					case (REGISTER_DECODE_16_DE << REGISTER_DECODE_LD_16_REG1_SHIFT):
						reg = &regs.main.de;
						break;
					case (REGISTER_DECODE_16_HL << REGISTER_DECODE_LD_16_REG1_SHIFT):
						reg = &regs.main.hl;
						break;
					case (REGISTER_DECODE_16_SP << REGISTER_DECODE_LD_16_REG1_SHIFT):
						reg = &regs.sp;
						break;
					}

					//Load 16-bit param
					(*reg) = (params[1] << 8) | params[0];

					return 0;
				}

				//Load IX from literal
				static u16 LD_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into IX
					regs.ixh = params[0];
					regs.ixl = params[1];

					return 0;
				}

				//Load address in HL from literal
				static u16 LD_ADDR_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into (HL)
					bus.memoryController.WriteMemory(regs.main.hl, params[0]);

					return 0;
				}

				//Load 8-bit register from value at address in HL
				static u16 LD_8_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8* reg = nullptr;

					switch (opcode.opcode & (REGISTER_DECODE_8_MASK << REGISTER_DECODE_LD_8_REG1_SHIFT))
					{
					case (REGISTER_DECODE_8_A << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.a;
						break;
					case (REGISTER_DECODE_8_B << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.b;
						break;
					case (REGISTER_DECODE_8_C << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.c;
						break;
					case (REGISTER_DECODE_8_D << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.d;
						break;
					case (REGISTER_DECODE_8_E << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.e;
						break;
					case (REGISTER_DECODE_8_H << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.h;
						break;
					case (REGISTER_DECODE_8_L << REGISTER_DECODE_LD_8_REG1_SHIFT):
						reg = &regs.main.l;
						break;
					}

					//Load param from value at (HL)
					(*reg) = bus.memoryController.ReadMemory(regs.main.hl);

					return 0;
				}
			}
		}
	}
}