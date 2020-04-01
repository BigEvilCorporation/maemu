#pragma once

#include "../Opcode.h"
#include "load.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
				static const int REGISTER_DECODE_ARITH_REG8_SHIFT = 0x0;
				static const int REGISTER_DECODE_ARITH_REG16_SHIFT = 0x4;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATION TEMPLATES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Add to A
				template <LoadFunc8 LOAD_8_T>
				u16 ADD_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add value to A
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u16 result = regs.main.a + value;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add to A (plus the C flag)
				template <LoadFunc8 LOAD_8_T>
				static u16 ADC_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add value + C flag to A
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u16 result = regs.main.a + value + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add two 16-bit registers
				template <LoadFunc16 LOAD_16_REG1_T, LoadFunc16 LOAD_16_REG2_T, StoreFunc16 STORE_16_T>
				static u16 ADD_16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load registers
					u16 reg1 = LOAD_16_REG1_T(opcode, params, regs, bus);
					u16 reg2 = LOAD_16_REG2_T(opcode, params, regs, bus);

					//Add together
					u32 result = reg1 + reg2;

					//Store result
					STORE_16_T(opcode, params, regs, bus, result);

					//Set flags
					ComputeFlagC_16(result, regs.main.f);
					SetFlagH((((reg2 ^ reg1 ^ result) >> 8)& FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return 0;
				}

				//Subtract from A
				template <LoadFunc8 LOAD_8_T>
				static u16 SUB_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract value from A
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u16 result = regs.main.a - value;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract from A (plus the C flag)
				template <LoadFunc8 LOAD_8_T>
				static u16 SBC_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract value + C flag from A
					u8 value = LOAD_8_T(opcode, params, regs, bus);
					u16 result = regs.main.a - value - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// ARITHMETIC OPERATIONS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Add 8-bit literal to A
				static auto ADD_A_n8 = ADD_A<LD_Fetch_n8>;

				//Add 8-bit register to A
				static auto ADD_A_r8 = ADD_A<LD_Fetch_r8>;

				//Add value at address in (HL) to A
				static auto ADD_A_dHL = ADD_A<LD_Fetch_dHL>;

				//Add value at address in (IX+offset) to A
				static auto ADD_A_dIX = ADD_A<LD_Fetch_dIXoff>;

				//Add value at address in (IY+offset) to A
				static auto ADD_A_dIY = ADD_A<LD_Fetch_dIYoff>;

				//Add IXH/IXL to A
				static auto ADD_A_IXHL = ADD_A<LD_Fetch_rIXHL>;

				//Add IYH/IYL to A
				static auto ADD_A_IYHL = ADD_A<LD_Fetch_rIYHL>;

				//Add 8-bit literal (plus the C flag) to A
				static auto ADC_A_n8 = ADC_A<LD_Fetch_n8>;

				//Add 8-bit register (plus the C flag) to A
				static auto ADC_A_r8 = ADC_A<LD_Fetch_r8>;

				//Add value at address in (HL) (plus the C flag) to A
				static auto ADC_A_dHL = ADC_A<LD_Fetch_dHL>;

				//Add value at address in (IX+offset) (plus the C flag) to A
				static auto ADC_A_dIX = ADC_A<LD_Fetch_dIXoff>;

				//Add value at address in (IY+offset) (plus the C flag) to A
				static auto ADC_A_dIY = ADC_A<LD_Fetch_dIYoff>;

				//Add IXH/IXL (plus the C flag) to A
				static auto ADC_A_IXHL = ADC_A<LD_Fetch_rIXHL>;

				//Add IYH/IYL (plus the C flag) to A
				static auto ADC_A_IYHL = ADC_A<LD_Fetch_rIYHL>;

				//Add 16-bit register to HL
				static auto ADD_HL_r16 = ADD_16<LD_Fetch_r16, LD_Fetch_rHL, LD_Store_rHL>;

				//Add 16-bit register to IX
				static auto ADD_IX_r16 = ADD_16<LD_Fetch_r16_IXHL, LD_Fetch_rIX, LD_Store_rIX>;

				//Add 16-bit register to IY
				static auto ADD_IY_r16 = ADD_16<LD_Fetch_r16_IYHL, LD_Fetch_rIY, LD_Store_rIY>;

				//Subtract 8-bit literal from A
				static auto SUB_A_n8 = SUB_A<LD_Fetch_n8>;

				//Subtract 8-bit register from A
				static auto SUB_A_r8 = SUB_A<LD_Fetch_r8>;

				//Subtract value at address in (HL) from A
				static auto SUB_A_dHL = SUB_A<LD_Fetch_dHL>;

				//Subtract value at address in (IX+offset) from A
				static auto SUB_A_dIX = SUB_A<LD_Fetch_dIXoff>;

				//Subtract value at address in (IY+offset) from A
				static auto SUB_A_dIY = SUB_A<LD_Fetch_dIYoff>;

				//Subtract IXH/IXL from A
				static auto SUB_A_IXHL = SUB_A<LD_Fetch_rIXHL>;

				//Subtract IYH/IYL from A
				static auto SUB_A_IYHL = SUB_A<LD_Fetch_rIYHL>;

				//Subtract 8-bit literal (plus the C flag) from A
				static auto SBC_A_n8 = SBC_A<LD_Fetch_n8>;

				//Subtract 8-bit register (plus the C flag) from A
				static auto SBC_A_r8 = SBC_A<LD_Fetch_r8>;

				//Subtract value at address in (HL) (plus the C flag) from A
				static auto SBC_A_dHL = SBC_A<LD_Fetch_dHL>;

				//Subtract value at address in (IX+offset) (plus the C flag) from A
				static auto SBC_A_dIX = SBC_A<LD_Fetch_dIXoff>;

				//Subtract value at address in (IY+offset) (plus the C flag) from A
				static auto SBC_A_dIY = SBC_A<LD_Fetch_dIYoff>;

				//Subtract IXH/IXL (plus the C flag) from A
				static auto SBC_A_IXHL = SBC_A<LD_Fetch_rIXHL>;

				//Subtract IYH/IYL (plus the C flag) from A
				static auto SBC_A_IYHL = SBC_A<LD_Fetch_rIYHL>;

				//Add 16-bit register (plus the C flag) to HL
				static u16 ADC_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u16 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u16 reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add reg + C flag to HL
					u32 result = regs.main.hl + reg + carry;

					//Set flags
					ComputeFlagZ_16(result, regs.main.f);
					ComputeFlagS_16(result, regs.main.f);
					ComputeFlagC_16(result, regs.main.f);
					SetFlagP(((regs.main.hl & 0x8000) == (reg & 0x8000) && (result & 0x8000) != (regs.main.hl & 0x8000)) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.hl ^ reg ^ result) >> 8)& FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					//Set result
					regs.main.hl = result;

					return 0;
				}

				//Subtract 16-bit register (plus the C flag) from HL
				static u16 SBC_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u16 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u16 reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Subtract reg + C flag from HL
					u32 result = regs.main.hl - reg - carry;

					//Set flags
					ComputeFlagZ_16(result, regs.main.f);
					ComputeFlagS_16(result, regs.main.f);
					ComputeFlagC_16(result, regs.main.f);
					SetFlagP(((regs.main.hl & 0x8000) != (reg & 0x8000) && (result & 0x8000) != (regs.main.hl & 0x8000)) ? 1 : 0, regs.main.f);
					SetFlagH((((regs.main.hl ^ reg ^ result) >> 8)& FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					//Set result
					regs.main.hl = result;

					return 0;
				}

				//Negate A
				static u16 NEG(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 prev = regs.main.a;

					//Negate A
					regs.main.a = -regs.main.a;

					//Determine flags (as if subtraction from 0)
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					ComputeFlagH(prev, regs.main.a, regs.main.f);
					SetFlagP((prev == 0x80) ? 1 : 0, regs.main.f);
					SetFlagC((prev != 0) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					return 0;
				}

				//Binary Coded Decimal correction on A
				static u16 DAA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 result = 0;

					//BCD lower nybble
					if (((regs.main.a & 0xF) > 0x9) || (regs.main.f & FLAG_H))
					{
						result |= 0x06;
					}

					//BCD higher nybble
					if ((regs.main.a > 0x99) || (regs.main.f & FLAG_C))
					{
						result |= 0x60;
						SetFlagC(1, regs.main.f);
					}
					else
					{
						SetFlagC(0, regs.main.f);
					}

					//Compute result
					if (CheckFlagN(regs.main.f))
					{
						result = regs.main.a - result;
					}
					else
					{
						result = regs.main.a + result;
					}

					//Set flags
					ComputeFlagZ(result, regs.main.f);
					ComputeFlagP(result, regs.main.f);
					ComputeFlagS(result, regs.main.f);
					SetFlagH(((regs.main.a & FLAG_H) ^ (result & FLAG_H)) ? 1 : 0, regs.main.f);

					//Set result
					regs.main.a = result;

					return 0;
				}

				//Rotate three nybbles - lower A and value at (HL) - to the left
				static u16 RLD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value in (HL)
					u8 lowerByte = bus.memoryController.ReadMemory(regs.main.hl);

					//Shift A and lo nybble into byte
					u8 lowerByteShifted = (regs.main.a & 0x0F) | (lowerByte << 4);

					//Lower byte back to (HL)
					bus.memoryController.WriteMemory(regs.main.hl, lowerByteShifted);

					//Original hi nybble to A
					regs.main.a = (regs.main.a & 0xF0) | ((lowerByte & 0xF0) >> 4);

					//Set flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagP(regs.main.a, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH(0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return 0;
				}

				//Rotate three nybbles - lower A and value at (HL) - to the right
				static u16 RRD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value in (HL)
					u8 lowerByte = bus.memoryController.ReadMemory(regs.main.hl);

					//Shift A and hi nybble into byte
					u8 lowerByteShifted = ((regs.main.a & 0x0F) << 4) | (lowerByte >> 4);

					//Lower byte back to (HL)
					bus.memoryController.WriteMemory(regs.main.hl, lowerByteShifted);

					//Original low nybble to A
					regs.main.a = (regs.main.a & 0xF0) | (lowerByte & 0x0F);

					//Set flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagP(regs.main.a, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH(0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return 0;
				}
			}
		}
	}
}