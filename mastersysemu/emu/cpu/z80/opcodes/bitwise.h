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
				static const int REGISTER_DECODE_BIT_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_SET_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_SHIFT_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_OR_8_REG_SHIFT = 0x0;
				static const int REGISTER_DECODE_AND_8_REG_SHIFT = 0x0;

				static const int REGISTER_DECODE_BIT_MASK = 0x07;
				static const int REGISTER_DECODE_BIT_SHIFT = 0x03;

				//Set specified bit in an 8-bit register
				static u16 SET_b_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SET_8_REG_SHIFT);

					//Bit in first param
					reg |= (1 << params[0]);
				}

				//Test specified bit on an 8-bit register
				static u16 BIT_b_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_BIT_8_REG_SHIFT);

					//Determine bit
					u8 bitIdx = (opcode.opcode >> REGISTER_DECODE_BIT_SHIFT) & REGISTER_DECODE_BIT_MASK;

					//Set Z flag to bit
					SetFlagZ((reg >> bitIdx) & 1, regs.main.f);

					return 0;
				}

				//Arithmetic shift an 8-bit register to the left
				static u16 SLA_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Copy top bit to C flag
					SetFlagC(reg >> 7, regs.main.f);

					//Shift left
					reg <<= 1;

					//Set Z, P, S flags
					ComputeFlagsZPS(reg, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Non-arithmetic shift an 8-bit register to the right
				static u16 SRL_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Copy bottom bit to C flag
					SetFlagC(reg & 1, regs.main.f);

					//Shift right
					reg >>= 1;

					//Set Z, P, flags
					ComputeFlagsZP(reg, regs.main.f);

					//Reset S, H, N
					SetFlag(FLAG_S, false, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

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

					//Store value
					bus.memoryController.WriteMemory(regs.ix + params[0], value);

					//Set Z, P, S flags
					ComputeFlagsZPS(value, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

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

					//Store value
					bus.memoryController.WriteMemory(regs.iy + params[0], value);

					//Set Z, P, S flags
					ComputeFlagsZPS(value, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);
				}

				//Rotate A to the left
				static u16 RLCA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy bit 7 (sign)
					u8 bit7 = (regs.main.a >> 7);

					//Rotate left
					regs.main.a = (regs.main.a << 1) | bit7;

					//Set flags
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate an 8-bit register to the left
				static u16 RLC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Copy bit 7 (sign)
					u8 bit7 = (reg >> 7);

					//Rotate left
					reg = (reg << 1) | bit7;

					//Set flags
					ComputeFlagsZPS(reg, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate A to the right
				static u16 RRCA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy bit 0
					u8 bit0 = (regs.main.a & 0x1);

					//Rotate right
					regs.main.a = (regs.main.a >> 1) | (bit0 << 7);

					//Set flags
					SetFlag(FLAG_C, bit0 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate A to the left (incl. carry flag)
				static u16 RLA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy C flag and bit 7
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;
					u8 bit7 = (regs.main.a >> 7);

					//Rotate left
					regs.main.a = (regs.main.a << 1) | carry;

					//Set flags
					SetFlagC(bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate A to the right (incl. carry flag)
				static u16 RRA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Take C flag and bit 0
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;
					u8 bit0 = (regs.main.a & 0x1);

					//Rotate right
					regs.main.a = (regs.main.a >> 1) | (carry << 7);

					//Set flags
					SetFlag(FLAG_C, bit0 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate value at address in (IX+offset) to the left
				static u16 RLC_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address (IX+offset)
					u16 address = regs.ix + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Copy bit 7 (sign)
					u8 bit7 = (value >> 7);

					//Rotate left
					value = (value << 1) | bit7;

					//Store value in memory
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZPS(value, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate value at address in (IX+offset) to the left, and copy result to 8-bit register
				static u16 RLC_dIX_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address (IX+offset)
					u16 address = regs.ix + params[0];

					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Read value
					reg = bus.memoryController.ReadMemory(address);

					//Copy bit 7 (sign)
					u8 bit7 = (reg >> 7);

					//Rotate left
					reg = (reg << 1) | bit7;

					//Store value in memory
					bus.memoryController.WriteMemory(address, reg);

					//Set flags
					ComputeFlagsZPS(reg, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate value at address in (IY+offset) to the left
				static u16 RLC_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address (IY+offset)
					u16 address = regs.iy + params[0];

					//Read value
					u8 value = bus.memoryController.ReadMemory(address);

					//Copy bit 7 (sign)
					u8 bit7 = (value >> 7);

					//Rotate left
					value = (value << 1) | bit7;

					//Store value in memory
					bus.memoryController.WriteMemory(address, value);

					//Set flags
					ComputeFlagsZPS(value, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate value at address in (IY+offset) to the left, and copy result to 8-bit register
				static u16 RLC_dIY_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Get address (IY+offset)
					u16 address = regs.iy + params[0];

					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Read value
					reg = bus.memoryController.ReadMemory(address);

					//Copy bit 7 (sign)
					u8 bit7 = (reg >> 7);

					//Rotate left
					reg = (reg << 1) | bit7;

					//Store value in memory
					bus.memoryController.WriteMemory(address, reg);

					//Set flags
					ComputeFlagsZPS(reg, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Logic OR A with 8-bit register
				static u16 OR_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//OR A with reg
					regs.main.a |= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with IXH/IXL
				static u16 OR_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//OR A with reg
					regs.main.a |= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with IYH/IYL
				static u16 OR_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//OR A with reg
					regs.main.a |= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with 8-bit literal
				static u16 OR_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//OR A with param
					regs.main.a |= params[0];

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with value at address in (HL)
				static u16 OR_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//OR A with (HL)
					regs.main.a |= bus.memoryController.ReadMemory(regs.main.hl);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with value at address in (IX+offset)
				static u16 OR_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//OR A with (IX+offset)
					regs.main.a |= bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic OR A with value at address in (IY+offset)
				static u16 OR_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//OR A with (IY+offset)
					regs.main.a |= bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with 8-bit register
				static u16 AND_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_AND_8_REG_SHIFT);

					//AND A with reg
					regs.main.a &= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with IXH/IXL
				static u16 AND_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_AND_8_REG_SHIFT);

					//AND A with reg
					regs.main.a &= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with IYH/IYL
				static u16 AND_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_AND_8_REG_SHIFT);

					//AND A with reg
					regs.main.a &= reg;

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

				//Logic AND A with value at address in (HL)
				static u16 AND_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with (HL)
					regs.main.a &= bus.memoryController.ReadMemory(regs.main.hl);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with value at address in (IX+offset)
				static u16 AND_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with (IX+offset)
					regs.main.a &= bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND A with value at address in (IY+offset)
				static u16 AND_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with (IY+offset)
					regs.main.a &= bus.memoryController.ReadMemory(regs.iy + params[0]);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with 8-bit register
				static u16 XOR_A_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//XOR A with reg
					regs.main.a ^= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with IXH/IXL
				static u16 XOR_A_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//XOR A with reg
					regs.main.a ^= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with IYH/IYL
				static u16 XOR_A_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_OR_8_REG_SHIFT);

					//XOR A with reg
					regs.main.a ^= reg;

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with 8-bit literal
				static u16 XOR_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with param
					regs.main.a ^= params[0];

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with value at address in (HL)
				static u16 XOR_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with (HL)
					regs.main.a ^= bus.memoryController.ReadMemory(regs.main.hl);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with value at address in (IX+offset)
				static u16 XOR_A_dIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with (IX+offset)
					regs.main.a ^= bus.memoryController.ReadMemory(regs.ix + params[0]);

					//Set flags
					ComputeFlagsZCS(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR A with value at address in (IY+offset)
				static u16 XOR_A_dIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with (IY+offset)
					regs.main.a ^= bus.memoryController.ReadMemory(regs.iy + params[0]);

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