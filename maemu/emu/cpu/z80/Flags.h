#pragma once

#include <ion/maths/Maths.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			enum Flags
			{
				FLAG_C  = (1 << 0),	//Carry
				FLAG_N  = (1 << 1),	//Subtract
				FLAG_PV = (1 << 2),	//Parity/Overflow
				FLAG_F3 = (1 << 3),	//Undocumented
				FLAG_H  = (1 << 4),	//Half carry
				FLAG_F5 = (1 << 5),	//Undocumented
				FLAG_Z  = (1 << 6),	//Zero
				FLAG_S  = (1 << 7),	//Sign
			};

			enum FlagIdxs
			{
				FLAG_INDEX_C,		//Carry
				FLAG_INDEX_N,		//Subtract
				FLAG_INDEX_PV,		//Parity/Overflow
				FLAG_INDEX_F3,		//Undocumented
				FLAG_INDEX_H,		//Half carry
				FLAG_INDEX_F5,		//Undocumented
				FLAG_INDEX_Z,		//Zero
				FLAG_INDEX_S,		//Sign
			};

			static bool CheckParity(u8 value)
			{
				value ^= value >> 4;
				value ^= value >> 2;
				value ^= value >> 1;
				return (~value) & 1;
			}

			static void SetFlag(u8 flag, bool value, u8& flags)
			{
				flags ^= (-(value ? 1 : 0) ^ flags) & flag;
			}

			static void SetFlagZ(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_Z);
			}

			static void SetFlagC(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_C);
			}

			static void SetFlagH(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_H);
			}

			static void SetFlagN(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_N);
			}

			static void SetFlagP(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_PV);
			}

			static void SetFlagS(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_S);
			}

			static bool CheckFlagZ(u8& flags)
			{
				return (flags & FLAG_Z) != 0;
			}

			static bool CheckFlagC(u8& flags)
			{
				return (flags & FLAG_C) != 0;
			}

			static bool CheckFlagS(u8& flags)
			{
				return (flags & FLAG_S) != 0;
			}

			static bool CheckFlagP(u8& flags)
			{
				return (flags & FLAG_PV) != 0;
			}

			static bool CheckFlagN(u8& flags)
			{
				return (flags & FLAG_N) != 0;
			}

			static void ComputeFlagZ(u16 diff, u8& flags)
			{
				//Zero flag if 0
				if ((diff & 0xFF) == 0)
					flags |= FLAG_Z;
				else
					flags &= ~FLAG_Z;
			}

			static void ComputeFlagZ_16(u32 diff, u8& flags)
			{
				//Zero flag if 0
				if ((diff & 0xFFFF) == 0)
					flags |= FLAG_Z;
				else
					flags &= ~FLAG_Z;
			}

			static void ComputeFlagS(u16 diff, u8& flags)
			{
				//Sign flag if bit 7 (signed overflow)
				if (diff & 0x80)
					flags |= FLAG_S;
				else
					flags &= ~FLAG_S;
			}

			static void ComputeFlagS_16(u32 diff, u8& flags)
			{
				//Sign flag if bit 15 (signed overflow)
				if (diff & 0x8000)
					flags |= FLAG_S;
				else
					flags &= ~FLAG_S;
			}

			static void ComputeFlagC(u16 diff, u8& flags)
			{
				//Carry flag if bit 8 (unsigned overflow)
				if (diff & 0x100)
					flags |= FLAG_C;
				else
					flags &= ~FLAG_C;
			}

			static void ComputeFlagC_16(u32 diff, u8& flags)
			{
				//Carry flag if bit 16 (unsigned overflow)
				if (diff & 0x10000)
					flags |= FLAG_C;
				else
					flags &= ~FLAG_C;
			}

			static void ComputeFlagH(u8 prev, u8 diff, u8& flags)
			{
				//Half-carry flag if bit 4 borrowed
				if((prev & 0x10) != (diff & 0x10))
					flags |= FLAG_H;
				else
					flags &= ~FLAG_H;
			}

			static void ComputeFlagP(u8 diff, u8& flags)
			{
				//Parity flag if even bits set
				if (CheckParity((u8)diff))
					flags |= FLAG_PV;
				else
					flags &= ~FLAG_PV;
			}

			static void ComputeFlagV(u8 prev, u8 diff, u8& flags)
			{
				if (diff > prev)
				{
					//Overflow if prev value was 0x7F
					if (prev == 0x7F)
						flags |= FLAG_PV;
					else
						flags &= ~FLAG_PV;
				}
				else if (diff < prev)
				{
					//Overflow if prev value was 0x80
					if (prev == 0x80)
						flags |= FLAG_PV;
					else
						flags &= ~FLAG_PV;
				}
				else
				{
					flags &= ~FLAG_PV;
				}
			}

			static void ComputeFlags_ArithmeticADD(u8 prev, u8 value, u16 result, u8& flags)
			{
				ComputeFlagZ(result, flags);
				ComputeFlagS(result, flags);
				ComputeFlagC(result, flags);
				SetFlagP(((prev & 0x80) == (value & 0x80) && (result & 0x80) != (prev & 0x80)) ? 1 : 0, flags);
				SetFlagH(((prev ^ value ^ result) & FLAG_H) ? 1 : 0, flags);
				SetFlagN(0, flags);
			}

			static void ComputeFlags_ArithmeticSUB(u8 prev, u8 value, u16 result, u8& flags)
			{
				ComputeFlagZ(result, flags);
				ComputeFlagS(result, flags);
				ComputeFlagC(result, flags);
				SetFlagP(((prev & 0x80) != (value & 0x80) && (result & 0x80) != (prev & 0x80)) ? 1 : 0, flags);
				SetFlagH(((prev ^ value ^ result) & FLAG_H) ? 1 : 0, flags);
				SetFlagN(1, flags);
			}

			static void ComputeFlags_AND(u8 result, u8& flags)
			{
				ComputeFlagZ(result, flags);
				ComputeFlagS(result, flags);
				ComputeFlagP(result, flags);
				SetFlagH(1, flags);
				SetFlagC(0, flags);
				SetFlagN(0, flags);
			}

			static void ComputeFlags_OR(u8 result, u8& flags)
			{
				ComputeFlagZ(result, flags);
				ComputeFlagS(result, flags);
				ComputeFlagP(result, flags);
				SetFlagH(0, flags);
				SetFlagC(0, flags);
				SetFlagN(0, flags);
			}

			static void ComputeFlags_XOR(u8 result, u8& flags)
			{
				ComputeFlagZ(result, flags);
				ComputeFlagS(result, flags);
				ComputeFlagP(result, flags);
				SetFlagH(0, flags);
				SetFlagC(0, flags);
				SetFlagN(0, flags);
			}
		}
	}
}