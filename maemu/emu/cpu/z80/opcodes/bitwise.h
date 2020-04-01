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
				static const int REGISTER_DECODE_BIT_MASK = 0x07;
				static const int REGISTER_DECODE_BIT_SHIFT = 0x03;

				typedef u8(*ModifierFunc8)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value);
				typedef void(*TestFunc8)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value);

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// MODIFIERS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Set bit specified in 8-bit literal
				static u8 BW_Set_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					u8 bitIdx = (opcode.opcode >> REGISTER_DECODE_BIT_SHIFT) & REGISTER_DECODE_BIT_MASK;
					return value | (1 << bitIdx);
				}

				//Reset bit specified in 8-bit literal
				static u8 BW_Reset_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					u8 bitIdx = (opcode.opcode >> REGISTER_DECODE_BIT_SHIFT) & REGISTER_DECODE_BIT_MASK;
					return value & ~(1 << bitIdx);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// TESTS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Test bit specified in 8-bit literal, set Z flag
				static void BW_Bit_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					u8 bitIdx = (opcode.opcode >> REGISTER_DECODE_BIT_SHIFT) & REGISTER_DECODE_BIT_MASK;
					u8 result = ((value >> bitIdx) & 1);
					SetFlagZ(result ^ 1, regs.main.f);
					SetFlagP(result ^ 1, regs.main.f);
					SetFlagS((bitIdx == 7 && result) ? 1 : 0, regs.main.f);
					SetFlagH(1, regs.main.f);
					SetFlagN(0, regs.main.f);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATION TEMPLATES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Load, modify, store 8-bit value
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T, ModifierFunc8 MODIFY_8_T>
				u16 MODIFY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load, modify, store value
					STORE_8_T(opcode, params, regs, bus, MODIFY_8_T(opcode, params, regs, bus, LOAD_8_T(opcode, params, regs, bus)));

					return 0;
				}

				//Load and test value
				template <LoadFunc8 LOAD_8_T, TestFunc8 TEST_8_T>
				u16 TEST(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load and test value
					TEST_8_T(opcode, params, regs, bus, LOAD_8_T(opcode, params, regs, bus));

					return 0;
				}

				//Arithmetic shift to the left
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 SLA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy top bit to C flag
					SetFlagC(value >> 7, regs.main.f);

					//Shift left
					value <<= 1;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set Z, P, S flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Arithmetic shift to the left, leaving 1 in bottom bit
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 SLL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy top bit to C flag
					SetFlagC(value >> 7, regs.main.f);

					//Shift left, leave 1 in bottom bit
					value = (value << 1) | 0x1;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set Z, P, S flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Arithmetic shift to the right
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 SRA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy bit 0 to C flag
					SetFlagC(value & 1, regs.main.f);

					//Shift right, preserving bit 7 (sign)
					value = (value >> 1) | (value & 0x80);

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set Z, P, S flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);

					//Reset H and N
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Non-arithmetic shift to the right
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 SRL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy bottom bit to C flag
					SetFlagC(value & 1, regs.main.f);

					//Shift right
					value >>= 1;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set Z, P, flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);

					//Reset S, H, N
					SetFlag(FLAG_S, false, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate to the left
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 RLC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy bit 7 (sign)
					u8 bit7 = (value >> 7);

					//Rotate left
					value = (value << 1) | bit7;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate 8-bit register to the left (incl. carry flag)
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 RL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy C flag and bit 7
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;
					u8 bit7 = (value >> 7);

					//Rotate left
					value = (value << 1) | carry;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlagC(bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate value at address in (IX+offset) to the left, and copy result to 8-bit register
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T, StoreFunc8 STORE_REG_8_T>
				u16 RLC_CP(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy bit 7 (sign)
					u8 bit7 = (value >> 7);

					//Rotate left
					value = (value << 1) | bit7;

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Store reg
					STORE_REG_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlag(FLAG_C, bit7 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate to the right
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 RRC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Copy bit 0
					u8 bit0 = (value & 0x1);

					//Rotate right
					value = (value >> 1) | (bit0 << 7);

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlag(FLAG_C, bit0 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Rotate 8-bit register to the right (incl. carry flag)
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 RR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					u8 value = LOAD_8_T(opcode, params, regs, bus);

					//Take C flag and bit 0
					u8 carry = (regs.main.f & FLAG_C) >> FLAG_INDEX_C;
					u8 bit0 = (value & 0x1);

					//Rotate right
					value = (value >> 1) | (carry << 7);

					//Store value
					STORE_8_T(opcode, params, regs, bus, value);

					//Set flags
					ComputeFlagZ(value, regs.main.f);
					ComputeFlagP(value, regs.main.f);
					ComputeFlagS(value, regs.main.f);
					SetFlag(FLAG_C, bit0 != 0, regs.main.f);
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);

					return 0;
				}

				//Logic OR with A
				template <LoadFunc8 LOAD_8_T>
				static u16 OR_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//OR A with value
					regs.main.a |= LOAD_8_T(opcode, params, regs, bus);

					//Set flags
					ComputeFlags_OR(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic AND with A
				template <LoadFunc8 LOAD_8_T>
				static u16 AND_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//AND A with value
					regs.main.a &= LOAD_8_T(opcode, params, regs, bus);

					//Set flags
					ComputeFlags_AND(regs.main.a, regs.main.f);

					return 0;
				}

				//Logic XOR with A
				template <LoadFunc8 LOAD_8_T>
				static u16 XOR_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//XOR A with value
					regs.main.a ^= LOAD_8_T(opcode, params, regs, bus);

					//Set flags
					ComputeFlags_XOR(regs.main.a, regs.main.f);

					return 0;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// BIT OPERATIONS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Set specified bit in an 8-bit register
				static auto SET_b_r8 = MODIFY<LD_Fetch_r8, LD_Store_SRC_r8, BW_Set_n8>;

				//Set specified bit at address in (HL)
				static auto SET_b_dHL = MODIFY<LD_Fetch_dHL, LD_Store_dHL, BW_Set_n8>;

				//Set specified bit at address in (IX+offset)
				static auto SET_b_dIX = MODIFY<LD_Fetch_dIXoff, LD_Store_dIXoff, BW_Set_n8>;

				//Set specified bit at address in (IY+offset)
				static auto SET_b_dIY = MODIFY<LD_Fetch_dIYoff, LD_Store_dIYoff, BW_Set_n8>;

				//Reset specified bit in an 8-bit register
				static auto RES_b_r8 = MODIFY<LD_Fetch_r8, LD_Store_SRC_r8, BW_Reset_n8>;

				//Reset specified bit at address in (HL)
				static auto RES_b_dHL = MODIFY<LD_Fetch_dHL, LD_Store_dHL, BW_Reset_n8>;

				//Reset specified bit at address in (IX+offset)
				static auto RES_b_dIX = MODIFY<LD_Fetch_dIXoff, LD_Store_dIXoff, BW_Reset_n8>;

				//Reset specified bit at address in (IY+offset)
				static auto RES_b_dIY = MODIFY<LD_Fetch_dIYoff, LD_Store_dIYoff, BW_Reset_n8>;

				//Test specified bit on an 8-bit register
				static auto BIT_b_r8 = TEST<LD_Fetch_r8, BW_Bit_n8>;

				//Test specified bit at address in (HL)
				static auto BIT_b_dHL = TEST<LD_Fetch_dHL, BW_Bit_n8>;

				//Test specified bit at address in (IX + offset)
				static auto BIT_b_dIX = TEST<LD_Fetch_dIXoff, BW_Bit_n8>;

				//Test specified bit at address in (IY + offset)
				static auto BIT_b_dIY = TEST<LD_Fetch_dIYoff, BW_Bit_n8>;

				//Arithmetic shift an 8-bit register to the left
				static auto SLA_r8 = SLA<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Arithmetic shift value at address in (HL) to the left
				static auto SLA_dHL = SLA<LD_Fetch_dHL, LD_Store_dHL>;

				//Arithmetic shift value at address in (IX+offset) to the left
				static auto SLA_dIX = SLA<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Arithmetic shift value at address in (IY+offset) to the left
				static auto SLA_dIY = SLA<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Arithmetic shift an 8-bit register to the left, leaving 1 in bottom bit
				static auto SLL_r8 = SLL<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Arithmetic shift value at address in (HL) to the left, leaving 1 in bottom bit
				static auto SLL_dHL = SLL<LD_Fetch_dHL, LD_Store_dHL>;

				//Arithmetic shift value at address in (IX+offset) to the left, leaving 1 in bottom bit
				static auto SLL_dIX = SLL<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Arithmetic shift value at address in (IY+offset) to the left, leaving 1 in bottom bit
				static auto SLL_dIY = SLL<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Arithmetic shift an 8-bit register to the right
				static auto SRA_r8 = SRA<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Arithmetic shift value at address in (HL) to the right
				static auto SRA_dHL = SRA<LD_Fetch_dHL, LD_Store_dHL>;

				//Arithmetic shift value at address in (IX+offset) to the right
				static auto SRA_dIX = SRA<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Arithmetic shift value at address in (IY+offset) to the right
				static auto SRA_dIY = SRA<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Non-arithmetic shift an 8-bit register to the right
				static auto SRL_r8 = SRL<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Non-arithmetic shift value at address in (HL) to the right
				static auto SRL_dHL = SRL<LD_Fetch_dHL, LD_Store_dHL>;

				//Non-arithmetic shift value at address in (IX+offset) to the right
				static auto SRL_dIX = SRL<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Non-arithmetic shift value at address in (IY+offset) to the right
				static auto SRL_dIY = SRL<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Rotate an 8-bit register to the left
				static auto RLC_r8 = RLC<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Rotate value at address in (HL) to the left
				static auto RLC_dHL = RLC<LD_Fetch_dHL, LD_Store_dHL>;

				//Rotate value at address in (IX+offset) to the left
				static auto RLC_dIX = RLC<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Rotate value at address in (IY+offset) to the left
				static auto RLC_dIY = RLC<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Rotate value at address in (IX+offset) to the left, and copy result to 8-bit register
				static auto RLC_dIX_r8 = RLC_CP<LD_Fetch_dIXoff, LD_Store_dIXoff, LD_Store_DST_r8>;

				//Rotate value at address in (IY+offset) to the left, and copy result to 8-bit register
				static auto RLC_dIY_r8 = RLC_CP<LD_Fetch_dIYoff, LD_Store_dIYoff, LD_Store_DST_r8>;

				//Rotate 8-bit register to the left (incl. carry flag)
				static auto RL_r8 = RL<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Rotate value at address in (HL) to the left (incl. carry flag)
				static auto RL_dHL = RL<LD_Fetch_dHL, LD_Store_dHL>;

				//Rotate value at address in (IX+offset) to the left (incl. carry flag)
				static auto RL_dIX = RL<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Rotate value at address in (IY+offset) to the left (incl. carry flag)
				static auto RL_dIY = RL<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Rotate an 8-bit register to the right
				static auto RRC_r8 = RRC<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Rotate value at address in (HL) to the right
				static auto RRC_dHL = RRC<LD_Fetch_dHL, LD_Store_dHL>;

				//Rotate value at address in (IX+offset) to the right
				static auto RRC_dIX = RRC<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Rotate value at address in (IY+offset) to the right
				static auto RRC_dIY = RRC<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Rotate 8-bit register to the right (incl. carry flag)
				static auto RR_r8 = RR<LD_Fetch_r8, LD_Store_SRC_r8>;

				//Rotate value at address in (HL) to the right (incl. carry flag)
				static auto RR_dHL = RR<LD_Fetch_dHL, LD_Store_dHL>;

				//Rotate value at address in (IX+offset) to the right (incl. carry flag)
				static auto RR_dIX = RR<LD_Fetch_dIXoff, LD_Store_dIXoff>;

				//Rotate value at address in (IY+offset) to the right (incl. carry flag)
				static auto RR_dIY = RR<LD_Fetch_dIYoff, LD_Store_dIYoff>;

				//Logic OR A with 8-bit literal
				static auto OR_A_n8 = OR_A<LD_Fetch_n8>;

				//Logic OR A with 8-bit register
				static auto OR_A_r8 = OR_A<LD_Fetch_r8>;

				//Logic OR A with value at address in (HL)
				static auto OR_A_dHL = OR_A<LD_Fetch_dHL>;

				//Logic OR A with value at address in (IX+offset)
				static auto OR_A_dIX = OR_A<LD_Fetch_dIXoff>;

				//Logic OR A with value at address in (IY+offset)
				static auto OR_A_dIY = OR_A<LD_Fetch_dIYoff>;

				//Logic OR A with IXH/IXL
				static auto OR_A_IXHL = OR_A<LD_Fetch_rIXHL>;

				//Logic OR A with IYH/IYL
				static auto OR_A_IYHL = OR_A<LD_Fetch_rIYHL>;

				//Logic AND A with 8-bit literal
				static auto AND_A_n8 = AND_A<LD_Fetch_n8>;

				//Logic AND A with 8-bit register
				static auto AND_A_r8 = AND_A<LD_Fetch_r8>;

				//Logic AND A with value at address in (HL)
				static auto AND_A_dHL = AND_A<LD_Fetch_dHL>;

				//Logic AND A with value at address in (IX+offset)
				static auto AND_A_dIX = AND_A<LD_Fetch_dIXoff>;

				//Logic AND A with value at address in (IY+offset)
				static auto AND_A_dIY = AND_A<LD_Fetch_dIYoff>;

				//Logic AND A with IXH/IXL
				static auto AND_A_IXHL = AND_A<LD_Fetch_rIXHL>;

				//Logic AND A with IYH/IYL
				static auto AND_A_IYHL = AND_A<LD_Fetch_rIYHL>;

				//Logic XOR A with 8-bit literal
				static auto XOR_A_n8 = XOR_A<LD_Fetch_n8>;

				//Logic XOR A with 8-bit register
				static auto XOR_A_r8 = XOR_A<LD_Fetch_r8>;

				//Logic XOR A with value at address in (HL)
				static auto XOR_A_dHL = XOR_A<LD_Fetch_dHL>;

				//Logic XOR A with value at address in (IX+offset)
				static auto XOR_A_dIX = XOR_A<LD_Fetch_dIXoff>;

				//Logic XOR A with value at address in (IY+offset)
				static auto XOR_A_dIY = XOR_A<LD_Fetch_dIYoff>;

				//Logic XOR A with IXH/IXL
				static auto XOR_A_IXHL = XOR_A<LD_Fetch_rIXHL>;

				//Logic XOR A with IYH/IYL
				static auto XOR_A_IYHL = XOR_A<LD_Fetch_rIYHL>;

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

				//Invert A
				static u16 CPL_A(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					regs.main.a = ~regs.main.a;
					SetFlagH(1, regs.main.f);
					SetFlagN(1, regs.main.f);

					return 0;
				}
			}
		}
	}
}