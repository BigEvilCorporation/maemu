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
				static const int REGISTER_DECODE_ARITH_REG8_SHIFT = 0x0;
				static const int REGISTER_DECODE_ARITH_REG16_SHIFT = 0x4;

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

				//Add 8-bit literal to A
				static u16 ADD_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add param to A
					u16 result = regs.main.a + params[0];
					
					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, params[0], result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add 8-bit register to A
				static u16 ADD_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u16 result = regs.main.a + reg;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add IXH/IXL to A
				static u16 ADD_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u16 result = regs.main.a + reg;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add IYH/IYL to A
				static u16 ADD_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u16 result = regs.main.a + reg;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (HL) to A
				static u16 ADD_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Add (HL) to A
					u16 result = regs.main.a + value;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (IX+offset) to A
				static u16 ADD_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Add (IX+offset) to A
					u16 result = regs.main.a + value;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (IY+offset) to A
				static u16 ADD_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Add (IY+offset) to A
					u16 result = regs.main.a + value;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add 8-bit register (plus the C flag) to A
				static u16 ADC_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u16 result = regs.main.a + reg + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

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
					SetFlagH((((regs.main.hl ^ reg ^ result) >> 8) & FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					//Set result
					regs.main.hl = result;

					return 0;
				}

				//Add IXH/IXL (plus the C flag) to A
				static u16 ADC_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u16 result = regs.main.a + reg + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add IYH/IYL (plus the C flag) to A
				static u16 ADC_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u16 result = regs.main.a + reg + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add 8-bit literal (plus the C flag) to A
				static u16 ADC_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add param + C flag to A
					u16 result = regs.main.a + params[0] + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, params[0], result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (HL) (plus the C flag) to A
				static u16 ADC_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (HL) + C flag to A
					u16 result = regs.main.a + value + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (IX+offset) (plus the C flag) to A
				static u16 ADC_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (IX+offset) + C flag to A
					u16 result = regs.main.a + value + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add value at address in (IY+offset) (plus the C flag) to A
				static u16 ADC_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get value at (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (IY+offset) + C flag to A
					u16 result = regs.main.a + value + carry;

					//Determine flags
					ComputeFlags_ArithmeticADD(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Add 16-bit register to HL
				static u16 ADD_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to HL
					u32 result = regs.main.hl + reg;

					//Set flags
					ComputeFlagC_16(result, regs.main.f);
					SetFlagH((((regs.main.hl ^ reg ^ result) >> 8) & FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					//Set result
					regs.main.hl = result;

					return 0;
				}

				//Add 16-bit register to IX
				static u16 ADD_IX_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IX
					u32 result = regs.ix + reg;

					//Set flags
					ComputeFlagC_16(result, regs.main.f);
					SetFlagH((((regs.ix ^ reg ^ result) >> 8) & FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					//Set result
					regs.ix = result;

					return 0;
				}

				//Add 16-bit register to IY
				static u16 ADD_IY_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IY
					u32 result = regs.iy + reg;

					//Set flags
					ComputeFlagC_16(result, regs.main.f);
					SetFlagH((((regs.iy ^ reg ^ result) >> 8) & FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					//Set result
					regs.iy = result;

					return 0;
				}

				//Subtract 8-bit literal from A
				static u16 SUB_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract literal from A
					u16 result = regs.main.a - params[0];

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, params[0], result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract 8-bit register from A
				static u16 SUB_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u16 result = regs.main.a - reg;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract IXH/IXL from A
				static u16 SUB_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u16 result = regs.main.a - reg;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract IYH/IYL from A
				static u16 SUB_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8 reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u16 result = regs.main.a - reg;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (HL) from A
				static u16 SUB_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Subtract (HL) from A
					u16 result = regs.main.a - value;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (IX+offset) from A
				static u16 SUB_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Subtract (IX+offset) from A
					u16 result = regs.main.a - value;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (IY+offset) from A
				static u16 SUB_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Subtract (IY+offset) from A
					u16 result = regs.main.a - value;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract 8-bit register (plus the C flag) from A
				static u16 SBC_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u16 result = regs.main.a - reg - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

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
					SetFlagH((((regs.main.hl ^ reg ^ result) >> 8) & FLAG_H) ? 1 : 0, regs.main.f);
					SetFlagN(1, regs.main.f);

					//Set result
					regs.main.hl = result;

					return 0;
				}

				//Subtract IXH/IXL (plus the C flag) from A
				static u16 SBC_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u16 result = regs.main.a - reg - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract IYH/IYL (plus the C flag) from A
				static u16 SBC_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8 reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u16 result = regs.main.a - reg - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, reg, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract 8-bit literal (plus the C flag) from A
				static u16 SBC_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract param + C flag from A
					u16 result = regs.main.a - params[0] - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, params[0], result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (HL) (plus the C flag) from A
				static u16 SBC_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (HL) + C flag from A
					u16 result = regs.main.a - value - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (IX+offset) (plus the C flag) from A
				static u16 SBC_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (IX+offset) + C flag from A
					u16 result = regs.main.a - value - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

					return 0;
				}

				//Subtract value at address in (IY+offset) (plus the C flag) from A
				static u16 SBC_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value at (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (IY+offset) + C flag from A
					u16 result = regs.main.a - value - carry;

					//Determine flags
					ComputeFlags_ArithmeticSUB(regs.main.a, value, result, regs.main.f);

					//Set result
					regs.main.a = (u8)result;

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