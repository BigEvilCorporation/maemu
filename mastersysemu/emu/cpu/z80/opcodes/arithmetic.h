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
				static const int REGISTER_DECODE_ARITH_REG8_SHIFT = 0x3;
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
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (reg & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add IXH/IXL to A
				static u16 ADD_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (reg & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add IYH/IYL to A
				static u16 ADD_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (reg & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add value at address in (HL) to A
				static u16 ADD_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Add (HL) to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (value & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add value at address in (IX+offset) to A
				static u16 ADD_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Add (IX+offset) to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (value & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add value at address in (IY+offset) to A
				static u16 ADD_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Fetch value at (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Add (IY+offset) to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + (value & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add 8-bit register (plus the C flag) to A
				static u16 ADC_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((reg + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add 16-bit register (plus the C flag) to HL
				static u16 ADC_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u16 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add reg + C flag to HL
					u16 prev = regs.main.hl;
					u32 diff = regs.main.hl + reg + carry;
					regs.main.hl = diff;

					//Determine flags
					ComputeFlagZ(regs.main.hl, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.hl, regs.main.f);
					SetFlagH((((prev & 0xFFF) + ((reg + carry) & 0xFFF)) & 0x1000) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add IXH/IXL (plus the C flag) to A
				static u16 ADC_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((reg + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add IYH/IYL (plus the C flag) to A
				static u16 ADC_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add reg + C flag to A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + reg + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((reg + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((value + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((value + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a + value + carry;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);
					SetFlagH((((prev & 0xF) + ((value + carry) & 0xF)) & 0x10) ? 1 : 0, regs.main.f);

					return 0;
				}

				//Add 16-bit register to HL
				static u16 ADD_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to HL
					u16 prev = regs.main.hl;
					u32 diff = regs.main.hl + reg;
					regs.main.hl = diff;

					//Determine C/H flags
					ComputeFlagC_16(diff, regs.main.f);
					SetFlagH((((prev & 0xFFF) + (reg & 0xFFF)) & 0x1000) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return 0;
				}

				//Add 16-bit register to IX
				static u16 ADD_IX_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IX
					u16 prev = regs.ix;
					u32 diff = regs.ix + reg;
					regs.ix = diff;

					//Determine C/H flags
					ComputeFlagC_16(diff, regs.main.f);
					SetFlagH((((prev & 0xFFF) + (reg & 0xFFF)) & 0x1000) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

					return 0;
				}

				//Add 16-bit register to IY
				static u16 ADD_IY_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16 reg = DecodeReg16_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IY
					u16 prev = regs.iy;
					u32 diff = regs.iy + reg;
					regs.iy = diff;

					//Determine C/H flags
					ComputeFlagC_16(diff, regs.main.f);
					SetFlagH((((prev & 0xFFF) + (reg & 0xFFF)) & 0x1000) ? 1 : 0, regs.main.f);
					SetFlagN(0, regs.main.f);

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
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - reg;
					regs.main.a = (u8)diff;

					//Set flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract IXH/IXL from A
				static u16 SUB_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - reg;
					regs.main.a = (u8)diff;

					//Set flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract IYH/IYL from A
				static u16 SUB_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - reg;
					regs.main.a = (u8)diff;

					//Set flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (HL) from A
				static u16 SUB_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (HL)
					u8 value = bus.memoryController.ReadMemory(regs.main.hl);

					//Subtract (HL) from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IX+offset) from A
				static u16 SUB_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (IX+offset)
					u8 value = bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Subtract (IX+offset) from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IY+offset) from A
				static u16 SUB_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Read value from (IY+offset)
					u8 value = bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Subtract (IY+offset) from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - value;
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract 8-bit register (plus the C flag) from A
				static u16 SBC_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (reg + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract 16-bit register (plus the C flag) from HL
				static u16 SBC_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u16 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Subtract reg + C flag from HL
					u16 prev = regs.main.hl;
					u32 diff = regs.main.hl - (reg + carry);
					regs.main.hl = diff;

					//Determine flags
					ComputeFlagZ(regs.main.hl, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.hl, regs.main.f);

					return 0;
				}

				//Subtract IXH/IXL (plus the C flag) from A
				static u16 SBC_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (reg + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract IYH/IYL (plus the C flag) from A
				static u16 SBC_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract reg + C flag from A
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (reg + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (value + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (value + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

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
					u8 prev = regs.main.a;
					u16 diff = regs.main.a - (value + carry);
					regs.main.a = (u8)diff;

					//Determine flags
					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagC(diff, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

					return 0;
				}

				//Binary Coded Decimal correction on A
				static u16 DAA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u8 hi = regs.main.a >> 4;
					u8 lo = regs.main.a & 0xF;

					//BCD lower nybble
					if ((lo > 9) || (regs.main.f & FLAG_H))
					{
						regs.main.a += 0x06;
					}

					//BCD higher nybble
					if ((hi > 9) || (regs.main.f & FLAG_C))
					{
						regs.main.a += 0x60;
						SetFlagC(1, regs.main.f);
					}
					else
					{
						SetFlagC(0, regs.main.f);
					}

					ComputeFlagZ(regs.main.a, regs.main.f);
					ComputeFlagP(regs.main.a, regs.main.f);
					ComputeFlagS(regs.main.a, regs.main.f);

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