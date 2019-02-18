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

				//Add 8-bit literal to A
				static u16 ADD_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add param to A
					regs.main.a += params[0];

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add 8-bit register to A
				static u16 ADD_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					regs.main.a += reg;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add IXH/IXL to A
				static u16 ADD_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					regs.main.a += reg;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add IYH/IYL to A
				static u16 ADD_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Add to A
					regs.main.a += reg;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (HL) to A
				static u16 ADD_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add (HL) to A
					regs.main.a += bus.memoryController.ReadMemory(regs.main.hl);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (IX+offset) to A
				static u16 ADD_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add (IX+offset) to A
					regs.main.a += bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (IY+offset) to A
				static u16 ADD_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Add (IY+offset) to A
					regs.main.a += bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += reg + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += reg + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += reg + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add 8-bit literal (plus the C flag) to A
				static u16 ADC_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add param + C flag to A
					regs.main.a += params[0] + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (HL) (plus the C flag) to A
				static u16 ADC_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (HL) + C flag to A
					regs.main.a += bus.memoryController.ReadMemory(regs.main.hl) + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (IX+offset) (plus the C flag) to A
				static u16 ADC_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (IX+offset) + C flag to A
					regs.main.a += bus.memoryController.ReadMemory(regs.ix + params[0]) + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add value at address in (IY+offset) (plus the C flag) to A
				static u16 ADC_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Add (IY+offset) + C flag to A
					regs.main.a += bus.memoryController.ReadMemory(regs.iy + params[0]) + carry;

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Add 16-bit register to HL
				static u16 ADD_HL_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to HL
					regs.main.hl += reg;

					//Determine C/H flags
					ComputeFlagsHC(regs.main.hl, regs.main.f);

					return 0;
				}

				//Add 16-bit register to IX
				static u16 ADD_IX_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IX
					regs.ix += reg;

					//Determine C/H flags
					ComputeFlagsHC(regs.ix, regs.main.f);

					return 0;
				}

				//Add 16-bit register to IY
				static u16 ADD_IY_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u16& reg = DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG16_SHIFT);

					//Add to IX
					regs.iy += reg;

					//Determine C/H flags
					ComputeFlagsHC(regs.iy, regs.main.f);

					return 0;
				}

				//Subtract 8-bit literal from A
				static u16 SUB_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract literal from A
					regs.main.a -= params[0];

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract 8-bit register from A
				static u16 SUB_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					regs.main.a -= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract IXH/IXL from A
				static u16 SUB_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					regs.main.a -= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract IYH/IYL from A
				static u16 SUB_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_ARITH_REG8_SHIFT);

					//Subtract from A
					regs.main.a -= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (HL) from A
				static u16 SUB_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract (HL) from A
					regs.main.a -= bus.memoryController.ReadMemory(regs.main.hl);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IX+offset) from A
				static u16 SUB_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract (IX+offset) from A
					regs.main.a -= bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IY+offset) from A
				static u16 SUB_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Subtract (IY+offset) from A
					regs.main.a -= bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += (reg + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += (reg + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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
					regs.main.a += (reg + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract 8-bit literal (plus the C flag) from A
				static u16 SBC_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract param + C flag from A
					regs.main.a += (params[0] + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (HL) (plus the C flag) from A
				static u16 SBC_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (HL) + C flag from A
					regs.main.a += (bus.memoryController.ReadMemory(regs.main.hl) + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IX+offset) (plus the C flag) from A
				static u16 SBC_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (IX+offset) + C flag from A
					regs.main.a += (bus.memoryController.ReadMemory(regs.ix + params[0]) + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Subtract value at address in (IY+offset) (plus the C flag) from A
				static u16 SBC_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get C flag
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;

					//Subtract (IY+offset) + C flag from A
					regs.main.a += (bus.memoryController.ReadMemory(regs.iy + params[0]) + carry);

					//Determine flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

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

					ComputeFlagsZPS(regs.main.a, regs.main.f);

					return 0;
				}
			}
		}
	}
}