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

					//Set Z/S flags
					ComputeFlagsZS(reg, regs.main.f);

					return 0;
				}

				//Arithmetic shift an 8-bit register to the right (preserving sign bit)
				//static u16 SRA_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				//{
				//}

				//Non-arithmetic shift an 8-bit register to the right
				static u16 SRL_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Determine reg
					u8& reg = DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_SHIFT_8_REG_SHIFT);

					//Copy bottom bit to C flag
					SetFlagC(reg & 1, regs.main.f);

					//Shift right
					reg >>= 1;

					//Set Z/S flags
					ComputeFlagsZS(reg, regs.main.f);

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

				//Rotate A to the left
				static u16 RLCA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Shift left 16-bit
					u16 shift = ((u16)regs.main.a << 1);

					//Back to A
					regs.main.a = (shift & 0xff);

					//Copy bit 7 to bit 0 and C flag
					u8 carry = (shift >> 8);
					regs.main.a = (regs.main.a & 0xFE) | carry;
					SetFlagC(carry, regs.main.f);

					return 0;
				}

				//Rotate A to the right
				static u16 RRCA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Shift to upper byte -1 bit
					u16 shift = ((u16)regs.main.a << 7);

					//Byte part back to A
					regs.main.a = (shift >> 8);

					//Copy bit 0 to bit 7
					regs.main.a = (regs.main.a & 0x7F) | (shift & 0xFF);

					//Copy bit 0 to C flag
					u8 carry = (shift >> 7);
					SetFlagC(carry, regs.main.f);

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

				//Logic AND A with 8-bit literal
				static u16 AND_A_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with literal
					regs.main.a &= params[0];

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

				//Logic XOR A with value at address in (HL)
				static u16 XOR_A_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with (HL)
					regs.main.a ^= bus.memoryController.ReadMemory(regs.main.hl);

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