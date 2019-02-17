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
				static const int REGISTER_DECODE_LD_8_REG1_SHIFT = 0x3;
				static const int REGISTER_DECODE_LD_8_REG2_SHIFT = 0x0;
				static const int REGISTER_DECODE_LD_16_REG1_SHIFT = 0x4;

				//Load 8-bit register from 8-bit literal
				static u16 LD_r8_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG1_SHIFT);

					//Load param
					reg = params[0];

					return 0;
				}

				//Load 8-bit register from another 8-bit register
				static u16 LD_r8_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine regs
					u8& reg1 = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG1_SHIFT);
					u8& reg2 = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG2_SHIFT);

					//Load
					reg1 = reg2;

					return 0;
				}

				//Load 8-bit register from IXH/IXL
				static u16 LD_r8_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					ion::debug::Log("LD_r8_IX() - not implemented");
					regs.internal.err = 1;
					return 0;
				}

				//Load IXH from 8-bit literal
				static u16 LD_IXH_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.ixh = params[0];
					return 0;
				}

				//Load IXL from 8-bit literal
				static u16 LD_IXL_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.ixl = params[0];
					return 0;
				}

				//Load IYH from 8-bit literal
				static u16 LD_IYH_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.iyh = params[0];
					return 0;
				}

				//Load IYL from 8-bit literal
				static u16 LD_IYL_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.iyl = params[0];
					return 0;
				}

				//Load A from I
				static u16 LD_A_I(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//A = I
					regs.main.a = regs.i;

					//Set flags ZS flags based on I
					ComputeFlagsZS(regs.i, regs.main.f);

					return 0;
				}

				//Load A from R
				static u16 LD_A_R(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//A = R
					regs.main.a = regs.r;

					//Set flags ZS flags based on R
					ComputeFlagsZS(regs.r, regs.main.f);

					return 0;
				}

				//Load 16-bit register from 16-bit literal
				static u16 LD_r16_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG1_SHIFT);

					//Load 16-bit param
					reg = (params[1] << 8) | params[0];

					return 0;
				}

				//Load HL from value at 16-bit literal address
				static u16 LD_HL_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Read value at address
					u8 lo = bus.memoryController.ReadMemory(address);
					u8 hi = bus.memoryController.ReadMemory(address + 1);
					regs.main.hl = (hi << 8) | lo;

					return 0;
				}

				//Load 16-bit register from value at 16-bit literal address
				static u16 LD_r16_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG1_SHIFT);

					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Read value at address
					u8 lo = bus.memoryController.ReadMemory(address);
					u8 hi = bus.memoryController.ReadMemory(address + 1);
					reg = (hi << 8) | lo;

					return 0;
				}

				//Load IX from value at 16-bit literal address
				static u16 LD_IX_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Read value at address
					u8 lo = bus.memoryController.ReadMemory(address);
					u8 hi = bus.memoryController.ReadMemory(address + 1);
					regs.ix = (hi << 8) | lo;

					return 0;
				}

				//Load IY from value at 16-bit literal address
				static u16 LD_IY_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Read value at address
					u8 lo = bus.memoryController.ReadMemory(address);
					u8 hi = bus.memoryController.ReadMemory(address + 1);
					regs.iy = (hi << 8) | lo;

					return 0;
				}

				//Load IX from 16-bit literal
				static u16 LD_IX_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into IX
					regs.ixh = params[0];
					regs.ixl = params[1];

					return 0;
				}

				//Load IY from 16-bit literal
				static u16 LD_IY_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into IY
					regs.iyh = params[0];
					regs.iyl = params[1];

					return 0;
				}

				//Load address in HL from 8-bit literal
				static u16 LD_dHL_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load param into (HL)
					bus.memoryController.WriteMemory(regs.main.hl, params[0]);

					return 0;
				}

				//Load address in HL from 8-bit register
				static u16 LD_dHL_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG2_SHIFT);

					//Load reg into (HL)
					bus.memoryController.WriteMemory(regs.main.hl, reg);

					return 0;
				}

				//Load address in (IX + offset) from 8-bit register
				static u16 LD_dIX_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG1_SHIFT);

					//Load reg into (IX + offset)
					bus.memoryController.WriteMemory(regs.ix + params[0], reg);

					return 0;
				}

				//Load address in (IY + offset) from 8-bit register
				static u16 LD_dIY_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG1_SHIFT);

					//Load reg into (IY + offset)
					bus.memoryController.WriteMemory(regs.iy + params[0], reg);

					return 0;
				}

				//Load address in (IX + offset) from 8-bit literal
				static u16 LD_dIX_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load literal into (IX + offset)
					bus.memoryController.WriteMemory(regs.ix + params[0], params[1]);

					return 0;
				}

				//Load address in (IY + offset) from 8-bit literal
				static u16 LD_dIY_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load literal into (IY + offset)
					bus.memoryController.WriteMemory(regs.iy + params[0], params[1]);

					return 0;
				}

				//Load 8-bit register from value at address in HL
				static u16 LD_r8_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG1_SHIFT);

					//Load param from value at (HL)
					reg = bus.memoryController.ReadMemory(regs.main.hl);

					return 0;
				}

				//Load A from value at literal address
				static u16 LD_A_d16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load into A
					regs.main.a = bus.memoryController.ReadMemory(address);

					return 0;
				}

				//Load literal address from A
				static u16 LD_n16_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load A into address
					bus.memoryController.WriteMemory(address, regs.main.a);

					return 0;
				}

				//Load A from address in (DE)
				static u16 LD_A_dDE(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load A from address in DE
					regs.main.a = bus.memoryController.ReadMemory(regs.main.de);

					return 0;
				}

				//Load address in (DE) from A
				static u16 LD_dDE_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load A into address in DE
					bus.memoryController.WriteMemory(regs.main.de, regs.main.a);

					return 0;
				}

				//Load literal address from 16-bit register
				static u16 LD_n16_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG1_SHIFT);

					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load reg into address
					bus.memoryController.WriteMemory(address, reg & 0xFF);
					bus.memoryController.WriteMemory(address + 1, reg >> 8);

					return 0;
				}

				//Load literal address from HL
				static u16 LD_n16_HL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load HL into address
					bus.memoryController.WriteMemory(address, regs.main.l);
					bus.memoryController.WriteMemory(address + 1, regs.main.h);

					return 0;
				}

				//Load literal address from IX
				static u16 LD_n16_IX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load IX into address
					bus.memoryController.WriteMemory(address, regs.ixl);
					bus.memoryController.WriteMemory(address + 1, regs.ixh);

					return 0;
				}

				//Load literal address from IY
				static u16 LD_n16_IY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address
					u16 address = (params[1] << 8) | params[0];

					//Load IX into address
					bus.memoryController.WriteMemory(address, regs.iyl);
					bus.memoryController.WriteMemory(address + 1, regs.iyh);

					return 0;
				}

				//Load address at (DE) from address at (HL), dec both regs and dec BC
				static u16 LDD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy from (HL) to (DE)
					bus.memoryController.WriteMemory(regs.main.de, bus.memoryController.ReadMemory(regs.main.hl));

					//Decrement addresses
					regs.main.hl--;
					regs.main.de--;

					//Decrement counter
					regs.main.bc--;

					return 0;
				}

				//Load address at (DE) from address at (HL), dec both regs, loop until BC == 0
				static u16 LDDR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy from (HL) to (DE)
					bus.memoryController.WriteMemory(regs.main.de, bus.memoryController.ReadMemory(regs.main.hl));

					//Decrement addresses
					regs.main.hl--;
					regs.main.de--;

					//Decrement counter
					regs.main.bc--;

					//If BC != 0, decrement PC to loop
					if (regs.main.bc != 0)
					{
						//This instruction + prefix = 2 bytes
						regs.pc -= 2;
					}

					return 0;
				}

				//Load address at (DE) from address at (HL), inc both regs, loop until BC == 0
				static u16 LDIR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy from (HL) to (DE)
					bus.memoryController.WriteMemory(regs.main.de, bus.memoryController.ReadMemory(regs.main.hl));

					//Increment addresses
					regs.main.hl++;
					regs.main.de++;

					//Decrement counter
					regs.main.bc--;

					//If BC != 0, decrement PC to loop
					if (regs.main.bc != 0)
					{
						//This instruction + prefix = 2 bytes
						regs.pc -= 2;
					}

					return 0;
				}
			}
		}
	}
}