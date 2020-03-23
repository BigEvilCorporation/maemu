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
				static const int REGISTER_DECODE_CP_8_REG_SHIFT = 0x0;

				//Compare A with 8-bit register
				static u16 CP_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_CP_8_REG_SHIFT);

					//Compare A with reg
					u16 result = (regs.main.a - reg);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					return 0;
				}

				//Compare A with IXH/IXL
				static u16 CP_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_CP_8_REG_SHIFT);

					//Compare A with reg
					u16 result = (regs.main.a - reg);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					return 0;
				}

				//Compare A with IYH/IYL
				static u16 CP_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_CP_8_REG_SHIFT);

					//Compare A with reg
					u16 result = (regs.main.a - reg);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					return 0;
				}

				//Compare A with 8-bit literal
				static u16 CP_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract literal from A
					u16 result = regs.main.a - params[0];

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, params[0], result, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (HL)
				static u16 CP_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Compare A with value at address in (HL)
					u16 result = (regs.main.a - value);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (IX+offset)
				static u16 CP_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Compare A with value at address in (IX+offset)
					u16 result = (regs.main.a - value);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (IY+offset)
				static u16 CP_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Compare A with value at address in (IY+offset)
					u16 result = (regs.main.a - value);

					//Set flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (HL), then increment HL and decrement BC
				static u16 CPI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at address in (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Compare A with value
					u16 diff = (regs.main.a - value);

					//Increment HL, decrement BC
					regs.main.hl++;
					regs.main.bc--;

					//Set flags
					ComputeFlagZ(diff, regs.main.f);
					ComputeFlagS(diff, regs.main.f);
					SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (HL), then increment HL and decrement BC while BC!=0 and A!=(HL)
				static u16 CPIR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					do
					{
						//Read value at address in (HL)
						u8 value = bus.memoryController.ReadMemory(regs.main.hl);

						//Compare A with value
						u16 diff = (regs.main.a - value);

						//Increment HL, decrement BC
						regs.main.hl++;
						regs.main.bc--;

						//Set flags
						ComputeFlagZ(diff, regs.main.f);
						ComputeFlagS(diff, regs.main.f);
						SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
						SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
						SetFlagN(1, regs.main.f);

					} while (regs.main.bc != 0 && !CheckFlagZ(regs.main.f));

					return 0;
				}

				//Compare A with value at address in (HL), then decrement HL and BC
				static u16 CPD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at address in (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Compare A with value
					u16 diff = (regs.main.a - value);

					//Decrement HL and BC
					regs.main.hl--;
					regs.main.bc--;

					//Set flags
					ComputeFlagZ(diff, regs.main.f);
					ComputeFlagS(diff, regs.main.f);
					SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					return 0;
				}

				//Compare A with value at address in (HL), then decrement HL and BC while BC!=0 and A!=(HL)
				static u16 CPDR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					do
					{
						//Read value at address in (HL)
						u8 value = bus.memoryController.ReadMemory(regs.main.hl);

						//Compare A with value
						u16 diff = (regs.main.a - value);

						//Decrement HL and BC
						regs.main.hl--;
						regs.main.bc--;

						//Set flags
						ComputeFlagZ(diff, regs.main.f);
						ComputeFlagS(diff, regs.main.f);
						SetFlagP((regs.main.bc != 0) ? 1 : 0, regs.main.f);
						SetFlagH((((regs.main.a & 0xF) - (value & 0xF)) < 0) ? 1 : 0, regs.main.f);
						SetFlagN(1, regs.main.f);

					} while (regs.main.bc != 0 && !CheckFlagZ(regs.main.f));

					return 0;
				}
			}
		}
	}
}