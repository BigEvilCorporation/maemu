#pragma once

#include "Constants.h"
#include "Registers.h"
#include "Flags.h"
#include "Bus.h"

#include <string>
#include <functional>

#include <ion/core/Types.h>
#include <ion/core/containers/FixedArray.h>
#include <ion/core/debug/Debug.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			//Opcode handler naming convention:
			//
			// r8  : 8-bit register
			// r16 : 16-bit register
			// n8  : 8-bit literal number
			// n16 : 16-bit literal number
			// d   : dereference register (read/write address)
			// b   : bit
			// a   : alt register
			//
			// e.g.:
			//   LD<LD_Fetch_n8, LD_Store_DST_r8>  : Load 8-bit register from 8-bit literal
			//   LD_dHL_r8 : Load address at HL from 8-bit register

			struct Opcode;

#if defined DEBUG
			class OpcodeParams
			{
			public:
				OpcodeParams() : count(0) {}

				u8& operator[](int index)
				{
					ion::debug::Assert(index >= 0 && index < count, "OpcodeParams::[]() - Out of bounds - is param count correct in opcode table?");
					return m_params[index];
				}

				const u8& operator[](int index) const
				{
					ion::debug::Assert(index >= 0 && index < count, "OpcodeParams::[]() - Out of bounds - is param count correct in opcode table?");
					return m_params[index];
				}

				u8 count;

			private:
				ion::FixedArray<u8, Z80_MAX_OPCODE_PARAMS> m_params;
			};
#else
			typedef ion::FixedArray<u8, Z80_MAX_OPCODE_PARAMS> OpcodeParams;
#endif

			typedef u16(*OpcodeHandler)(const Opcode& opcode, const OpcodeParams& params, Registers& regs, Bus& bus);

			struct Opcode
			{
				u8 opcode;
				u8 paramBytes;
				OpcodeHandler handler;
				std::string name;
				std::string paramsFormat;
			};

			enum RegisterDecode_8Bit
			{
				REGISTER_DECODE_8_MASK = 0x07,
				REGISTER_DECODE_8_A = 0x07,
				REGISTER_DECODE_8_B = 0x00,
				REGISTER_DECODE_8_C = 0x01,
				REGISTER_DECODE_8_D = 0x02,
				REGISTER_DECODE_8_E = 0x03,
				REGISTER_DECODE_8_H = 0x04,
				REGISTER_DECODE_8_IXH = 0x04,
				REGISTER_DECODE_8_IYH = 0x04,
				REGISTER_DECODE_8_L = 0x05,
				REGISTER_DECODE_8_IXL = 0x05,
				REGISTER_DECODE_8_IYL = 0x05
			};

			enum RegisterDecode_16Bit
			{
				REGISTER_DECODE_16_MASK = 0x03,
				REGISTER_DECODE_16_BC = 0x00,
				REGISTER_DECODE_16_DE = 0x01,
				REGISTER_DECODE_16_HL = 0x02,
				REGISTER_DECODE_16_SP = 0x03,
				REGISTER_DECODE_16_AF = 0x03,
			};

			enum RegisterDecode_Condition
			{
				REGISTER_DECODE_CONDITION_NZ,
				REGISTER_DECODE_CONDITION_Z,
				REGISTER_DECODE_CONDITION_NC,
				REGISTER_DECODE_CONDITION_C,
				REGISTER_DECODE_CONDITION_PO,
				REGISTER_DECODE_CONDITION_PE,
				REGISTER_DECODE_CONDITION_POS,
				REGISTER_DECODE_CONDITION_NEG,
				REGISTER_DECODE_CONDITION_MASK = 0x07
			};

			static u8& DecodeReg8(Registers& regs, u8 opcode, u8 shift)
			{
				u8* reg = nullptr;

				u8 regType = (opcode >> shift) & REGISTER_DECODE_8_MASK;

				switch (regType)
				{
				case (REGISTER_DECODE_8_A):
					reg = &regs.main.a;
					break;
				case (REGISTER_DECODE_8_B):
					reg = &regs.main.b;
					break;
				case (REGISTER_DECODE_8_C):
					reg = &regs.main.c;
					break;
				case (REGISTER_DECODE_8_D):
					reg = &regs.main.d;
					break;
				case (REGISTER_DECODE_8_E):
					reg = &regs.main.e;
					break;
				case (REGISTER_DECODE_8_H):
					reg = &regs.main.h;
					break;
				case (REGISTER_DECODE_8_L):
					reg = &regs.main.l;
					break;
				}

				if (!reg)
				{
					ion::debug::Error("DecodeReg8() - Could not decode register");
				}

				return *reg;
			}

			static u8& DecodeReg8_IX(Registers& regs, u8 opcode, u8 shift)
			{
				u8* reg = nullptr;

				u8 regType = (opcode >> shift) & REGISTER_DECODE_8_MASK;

				switch (regType)
				{
				case (REGISTER_DECODE_8_A):
					reg = &regs.main.a;
					break;
				case (REGISTER_DECODE_8_B):
					reg = &regs.main.b;
					break;
				case (REGISTER_DECODE_8_C):
					reg = &regs.main.c;
					break;
				case (REGISTER_DECODE_8_D):
					reg = &regs.main.d;
					break;
				case (REGISTER_DECODE_8_E):
					reg = &regs.main.e;
					break;
				case (REGISTER_DECODE_8_IXH):
					reg = &regs.ixh;
					break;
				case (REGISTER_DECODE_8_IXL):
					reg = &regs.ixl;
					break;
				}

				if (!reg)
				{
					ion::debug::Error("DecodeReg8_IX() - Could not decode register");
				}

				return *reg;
			}

			static u8& DecodeReg8_IY(Registers& regs, u8 opcode, u8 shift)
			{
				u8* reg = nullptr;

				u8 regType = (opcode >> shift) & REGISTER_DECODE_8_MASK;

				switch (regType)
				{
				case (REGISTER_DECODE_8_A):
					reg = &regs.main.a;
					break;
				case (REGISTER_DECODE_8_B):
					reg = &regs.main.b;
					break;
				case (REGISTER_DECODE_8_C):
					reg = &regs.main.c;
					break;
				case (REGISTER_DECODE_8_D):
					reg = &regs.main.d;
					break;
				case (REGISTER_DECODE_8_E):
					reg = &regs.main.e;
					break;
				case (REGISTER_DECODE_8_IYH):
					reg = &regs.iyh;
					break;
				case (REGISTER_DECODE_8_IYL):
					reg = &regs.iyl;
					break;
				}

				if (!reg)
				{
					ion::debug::Error("DecodeReg8_IY() - Could not decode register");
				}

				return *reg;
			}

			static u16& DecodeReg16(Registers& regs, u8 opcode, u8 shift)
			{
				u16* reg = nullptr;

				u8 regType = (opcode >> shift) & REGISTER_DECODE_16_MASK;

				switch (regType)
				{
				case (REGISTER_DECODE_16_BC):
					reg = &regs.main.bc;
					break;
				case (REGISTER_DECODE_16_DE):
					reg = &regs.main.de;
					break;
				case (REGISTER_DECODE_16_HL):
					reg = &regs.main.hl;
					break;
				case (REGISTER_DECODE_16_SP):
					reg = &regs.sp;
					break;
				}

				if (!reg)
				{
					ion::debug::Error("DecodeReg16() - Could not decode register");
				}

				return *reg;
			}

			static u16& DecodeReg16Stack(Registers& regs, u8 opcode, u8 shift)
			{
				u16* reg = nullptr;

				u8 regType = (opcode >> shift) & REGISTER_DECODE_16_MASK;

				switch (regType)
				{
				case (REGISTER_DECODE_16_BC):
					reg = &regs.main.bc;
					break;
				case (REGISTER_DECODE_16_DE):
					reg = &regs.main.de;
					break;
				case (REGISTER_DECODE_16_HL):
					reg = &regs.main.hl;
					break;
				case (REGISTER_DECODE_16_AF):
					reg = &regs.main.af;
					break;
				}

				if (!reg)
				{
					ion::debug::Error("DecodeReg16Stack() - Could not decode register");
				}

				return *reg;
			}

			static bool DecodeCondition(Registers& regs, u8 opcode, u8 shift)
			{
				bool result = false;
				u8 condition = (opcode >> shift) & REGISTER_DECODE_CONDITION_MASK;

				switch (condition)
				{
				case REGISTER_DECODE_CONDITION_NZ:
					result = !CheckFlagsZ(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_Z:
					result = CheckFlagsZ(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_NC:
					result = !CheckFlagsC(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_C:
					result = CheckFlagsC(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_PO:
					result = !CheckFlagsP(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_PE:
					result = CheckFlagsP(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_POS:
					result = !CheckFlagsS(regs.main.f);
					break;
				case REGISTER_DECODE_CONDITION_NEG:
					result = CheckFlagsS(regs.main.f);
					break;
				}

				return result;
			}
		}
	}
}