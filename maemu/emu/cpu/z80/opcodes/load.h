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
				static const int REGISTER_DECODE_LD_8_REG_SRC_SHIFT = 0x0;
				static const int REGISTER_DECODE_LD_8_REG_DST_SHIFT = 0x3;
				static const int REGISTER_DECODE_LD_16_REG_SRC_SHIFT = 0x4;
				static const int REGISTER_DECODE_LD_16_REG_DST_SHIFT = 0x4;

				typedef u8(*LoadFunc8)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus);
				typedef void(*StoreFunc8)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value);

				typedef u16(*LoadFunc16)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus);
				typedef void(*StoreFunc16)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value);
				
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 8-bit FETCHES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Load from 8-bit constant
				static u8 LD_Fetch_n8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return params[0];
				}

				//Load from 8-bit constant (second param)
				static u8 LD_Fetch_n8_1(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return params[1];
				}

				//Load 8-bit value from constant address
				static u8 LD_Fetch_n8_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 address = (params[1] << 8) | params[0];
					return bus.memoryController.ReadMemory(address);
				}

				//Load from 8-bit register
				static u8 LD_Fetch_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_SRC_SHIFT);
				}

				//Load from 8-bit register (incl. IXH/IXL)
				static u8 LD_Fetch_rIXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_SRC_SHIFT);
				}

				//Load from 8-bit register (incl. IYH/IYL)
				static u8 LD_Fetch_rIYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_SRC_SHIFT);
				}

				//Load A
				static u8 LD_Fetch_rA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.main.a;
				}

				//Load I
				static u8 LD_Fetch_rI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.i;
				}

				//Load R
				static u8 LD_Fetch_rR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.r;
				}

				//Load from address in HL
				static u8 LD_Fetch_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return bus.memoryController.ReadMemory(regs.main.hl);
				}

				//Load from address in BC
				static u8 LD_Fetch_dBC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return bus.memoryController.ReadMemory(regs.main.bc);
				}

				//Load from address in DE
				static u8 LD_Fetch_dDE(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return bus.memoryController.ReadMemory(regs.main.de);
				}

				//Load from address in IX + offset
				static u8 LD_Fetch_dIXoff(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return bus.memoryController.ReadMemory(regs.ix + params[0]);
				}

				//Load from address in IY + offset
				static u8 LD_Fetch_dIYoff(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return bus.memoryController.ReadMemory(regs.iy + params[0]);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 8-bit STORES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Store to source 8-bit register
				static void LD_Store_SRC_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_SRC_SHIFT) = value;
				}

				//Store to destination 8-bit register
				static void LD_Store_DST_r8(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					DecodeReg8(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_DST_SHIFT) = value;
				}

				//Store to constant address
				static void LD_Store_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					u16 address = (params[1] << 8) | params[0];
					bus.memoryController.WriteMemory(address, value);
				}

				//Store to 8-bit register (incl. IXH/IXL)
				static void LD_Store_rIXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					DecodeReg8_IX(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_DST_SHIFT) = value;
				}

				//Store to 8-bit register (incl. IYH/IYL)
				static void LD_Store_rIYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					DecodeReg8_IY(regs, opcode.opcode, REGISTER_DECODE_LD_8_REG_DST_SHIFT) = value;
				}

				//Store to A
				static void LD_Store_rA(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					regs.main.a = value;
				}

				//Store to I
				static void LD_Store_rI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					regs.i = value;
				}

				//Store to R
				static void LD_Store_rR(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					regs.r = value;
				}

				//Store to address in HL
				static void LD_Store_dHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					bus.memoryController.WriteMemory(regs.main.hl, value);
				}

				//Store to address in BC
				static void LD_Store_dBC(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					bus.memoryController.WriteMemory(regs.main.bc, value);
				}

				//Store to address in DE
				static void LD_Store_dDE(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					bus.memoryController.WriteMemory(regs.main.de, value);
				}

				//Store to address in IX + offset
				static void LD_Store_dIXoff(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					bus.memoryController.WriteMemory(regs.ix + params[0], value);
				}

				//Store to address in IY + offset
				static void LD_Store_dIYoff(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u8 value)
				{
					bus.memoryController.WriteMemory(regs.iy + params[0], value);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 16-bit FETCHES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Load from 16-bit constant
				static u16 LD_Fetch_n16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return (params[1] << 8) | params[0];
				}

				//Load 16-bit value from constant address
				static u16 LD_Fetch_n16_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					u16 address = (params[1] << 8) | params[0];
					return (bus.memoryController.ReadMemory(address + 1) << 8) | bus.memoryController.ReadMemory(address);
				}

				//Load from 16-bit register
				static u16 LD_Fetch_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG_SRC_SHIFT);
				}

				//Load from 16-bit register (incl. IXH/IXL)
				static u16 LD_Fetch_r16_IXHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg16_IX(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG_SRC_SHIFT);
				}

				//Load from 16-bit register (incl. IYH/IYL)
				static u16 LD_Fetch_r16_IYHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return DecodeReg16_IY(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG_SRC_SHIFT);
				}

				//Load from SP
				static u16 LD_Fetch_rSP(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.sp;
				}

				//Load from HL
				static u16 LD_Fetch_rHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.main.hl;
				}

				//Load from IX
				static u16 LD_Fetch_rIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.ix;
				}

				//Load from IY
				static u16 LD_Fetch_rIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					return regs.iy;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 16-bit STORES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Store to 16-bit register
				static void LD_Store_r16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					DecodeReg16(regs, opcode.opcode, REGISTER_DECODE_LD_16_REG_DST_SHIFT) = value;
				}

				//Store to literal address
				static void LD_Store_dn16(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					u16 address = (params[1] << 8) | params[0];
					bus.memoryController.WriteMemory(address, value & 0xFF);
					bus.memoryController.WriteMemory(address + 1, value >> 8);
				}

				//Store to IX
				static void LD_Store_rIX(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					regs.ix = value;
				}

				//Store to IY
				static void LD_Store_rIY(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					regs.iy = value;
				}

				//Store to SP
				static void LD_Store_rSP(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					regs.sp = value;
				}

				//Store to HL
				static void LD_Store_rHL(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus, u16 value)
				{
					regs.main.hl = value;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATION TEMPLATES
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Load 8-bit source to 8-bit destination
				template <LoadFunc8 LOAD_8_T, StoreFunc8 STORE_8_T>
				u16 LD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					STORE_8_T(opcode, params, regs, bus, LOAD_8_T(opcode, params, regs, bus));

					return 0;
				}

				//Load 16-bit source to 16-bit destination
				template <LoadFunc16 LOAD_16_T, StoreFunc16 STORE_16_T>
				u16 LD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Load value
					STORE_16_T(opcode, params, regs, bus, LOAD_16_T(opcode, params, regs, bus));

					return 0;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// OPERATIONS
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//Load 8-bit register from 8-bit literal
				static auto LD_r8_n8 = LD<LD_Fetch_n8, LD_Store_DST_r8>;

				//Load 16-bit register from 16-bit literal
				static auto LD_r16_n16 = LD<LD_Fetch_n16, LD_Store_r16>;

				//Load 8-bit register from another 8-bit register
				static auto LD_r8_r8 = LD<LD_Fetch_r8, LD_Store_DST_r8>;

				//Load IXH/IXL from 8-bit literal
				static auto LD_IXHL_n8 = LD<LD_Fetch_n8, LD_Store_rIXHL>;

				//Load IYH/IYL from 8-bit literal
				static auto LD_IYHL_n8 = LD<LD_Fetch_n8, LD_Store_rIYHL>;

				//Load 8-bit register from IXH/IXL
				static auto LD_r8_IXHL = LD<LD_Fetch_rIXHL, LD_Store_rIXHL>;

				//Load 8-bit register from IYH/IYL
				static auto LD_r8_IYHL = LD<LD_Fetch_rIYHL, LD_Store_rIYHL>;

				//Load I from A
				static auto LD_I_A = LD<LD_Fetch_rA, LD_Store_rI>;

				//Load A from I
				static auto LD_A_I = LD<LD_Fetch_rI, LD_Store_rA>;

				//Load R from A
				static auto LD_R_A = LD<LD_Fetch_rA, LD_Store_rR>;

				//Load A from R
				static auto LD_A_R = LD<LD_Fetch_rR, LD_Store_rA>;

				//Load 16-bit register from value at 16-bit literal address
				static auto LD_r16_dn16 = LD<LD_Fetch_n16_dn16, LD_Store_r16>;

				//Load IX from value at 16-bit literal address
				static auto LD_IX_dn16 = LD<LD_Fetch_n16_dn16, LD_Store_rIX>;

				//Load IY from value at 16-bit literal address
				static auto LD_IY_dn16 = LD<LD_Fetch_n16_dn16, LD_Store_rIY>;

				//Load IX from 16-bit literal
				static auto LD_IX_n16 = LD<LD_Fetch_n16, LD_Store_rIX>;

				//Load IY from 16-bit literal
				static auto LD_IY_n16 = LD<LD_Fetch_n16, LD_Store_rIY>;

				//Load SP from HL
				static auto LD_SP_HL = LD<LD_Fetch_rHL, LD_Store_rSP>;

				//Load address in BC from A
				static auto LD_dBC_A = LD<LD_Fetch_rA, LD_Store_dBC>;

				//Load address in HL from 8-bit literal
				static auto LD_dHL_n8 = LD<LD_Fetch_n8, LD_Store_dHL>;

				//Load address in HL from 8-bit register
				static auto LD_dHL_r8 = LD<LD_Fetch_r8, LD_Store_dHL>;

				//Load 8-bit register from value at address in HL
				static auto LD_r8_dHL = LD<LD_Fetch_dHL, LD_Store_DST_r8>;

				//Load A from value at literal address
				static auto LD_A_d16 = LD<LD_Fetch_n8_dn16, LD_Store_rA>;

				//Load literal address from A
				static auto LD_n16_A = LD<LD_Fetch_rA, LD_Store_dn16>;

				//Load A from address in (DE)
				static auto LD_A_dDE = LD<LD_Fetch_dDE, LD_Store_rA>;

				//Load A from address in (BC)
				static auto LD_A_dBC = LD<LD_Fetch_dBC, LD_Store_rA>;

				//Load address in (DE) from A
				static auto LD_dDE_A = LD<LD_Fetch_rA, LD_Store_dDE>;

				//Load literal address from 16-bit register
				static auto LD_n16_r16 = LD<LD_Fetch_r16, LD_Store_dn16>;

				//Load literal address from HL
				static auto LD_n16_HL = LD<LD_Fetch_rHL, LD_Store_dn16>;

				//Load literal address from IX
				static auto LD_n16_IX = LD<LD_Fetch_rIX, LD_Store_dn16>;

				//Load literal address from IY
				static auto LD_n16_IY = LD<LD_Fetch_rIY, LD_Store_dn16>;

				//Load 8-bit register from address in (IX + offset)
				static auto LD_r8_dIX = LD<LD_Fetch_dIXoff, LD_Store_DST_r8>;

				//Load 8-bit register from address in (IY + offset)
				static auto LD_r8_dIY = LD<LD_Fetch_dIYoff, LD_Store_DST_r8>;

				//Load address in (IX + offset) from 8-bit register
				static auto LD_dIX_r8 = LD<LD_Fetch_r8, LD_Store_dIXoff>;

				//Load address in (IY + offset) from 8-bit register
				static auto LD_dIY_r8 = LD<LD_Fetch_r8, LD_Store_dIYoff>;

				//Load address in (IX + offset) from 8-bit literal
				static auto LD_dIX_n8 = LD<LD_Fetch_n8_1, LD_Store_dIXoff>;

				//Load address in (IY + offset) from 8-bit literal
				static auto LD_dIY_n8 = LD<LD_Fetch_n8_1, LD_Store_dIYoff>;

				//Load address at (DE) from address at (HL), dec DE and HL, dec BC
				static u16 LDD(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy from (HL) to (DE)
					bus.memoryController.WriteMemory(regs.main.de, bus.memoryController.ReadMemory(regs.main.hl));

					//Decrement addresses
					regs.main.hl--;
					regs.main.de--;

					//Decrement counter
					regs.main.bc--;

					//Set flags
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);
					SetFlag(FLAG_PV, regs.main.bc != 0, regs.main.f);

					return 0;
				}

				//Load address at (DE) from address at (HL), inc DE and HL, dec BC
				static u16 LDI(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus)
				{
					//Copy from (HL) to (DE)
					bus.memoryController.WriteMemory(regs.main.de, bus.memoryController.ReadMemory(regs.main.hl));

					//Increment addresses
					regs.main.hl++;
					regs.main.de++;

					//Decrement counter
					regs.main.bc--;

					//Set flags
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);
					SetFlag(FLAG_PV, regs.main.bc != 0, regs.main.f);

					return 0;
				}

				//Load address at (DE) from address at (HL), dec DE and HL, dec BC, loop until BC == 0
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

					//Set flags
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);
					SetFlag(FLAG_PV, regs.main.bc != 0, regs.main.f);

					return 0;
				}

				//Load address at (DE) from address at (HL), inc DE and HL, dec BC, loop until BC == 0
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

					//Set flags
					SetFlag(FLAG_H, false, regs.main.f);
					SetFlag(FLAG_N, false, regs.main.f);
					SetFlag(FLAG_PV, regs.main.bc != 0, regs.main.f);

					return 0;
				}
			}
		}
	}
}