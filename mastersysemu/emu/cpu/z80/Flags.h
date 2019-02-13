#pragma once

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

			static void SetFlagZ(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_Z);
			}

			static void SetFlagC(u8 value, u8& flags)
			{
				flags ^= (-value ^ flags) & (1 << FLAG_INDEX_C);
			}

			static bool CheckFlagsZ(u8& flags)
			{
				return (flags & FLAG_Z) != 0;
			}

			static bool CheckFlagsC(u8& flags)
			{
				return (flags & FLAG_C) != 0;
			}

			static bool CheckFlagsS(u8& flags)
			{
				return (flags & FLAG_S) != 0;
			}

			static bool CheckFlagsP(u8& flags)
			{
				return (flags & FLAG_PV) != 0;
			}

			static void ComputeFlagsZCS(u16 diff, u8& flags)
			{
				//Zero flag if 0
				if ((diff & 0xFF) == 0)
					flags |= FLAG_Z;
				else
					flags &= ~FLAG_Z;

				//Carry flag if bit 8 (unsigned overflow)
				if (diff & 0x100)
					flags |= FLAG_C;
				else
					flags &= ~FLAG_C;

				//Sign flag if bit 7 (signed overflow)
				if (diff & 0x80)
					flags |= FLAG_S;
				else
					flags &= ~FLAG_S;
			}

			static void ComputeFlagsZS(u16 diff, u8& flags)
			{
				//Zero flag if 0
				if ((diff & 0xFF) == 0)
					flags |= FLAG_Z;
				else
					flags &= ~FLAG_Z;

				//Sign flag if bit 7 (signed overflow)
				if (diff & 0x80)
					flags |= FLAG_S;
				else
					flags &= ~FLAG_S;
			}

			static void ComputeFlagsZ(u16 diff, u8& flags)
			{
				//Zero flag if 0
				if ((diff & 0xFF) == 0)
					flags |= FLAG_Z;
				else
					flags &= ~FLAG_Z;
			}

			static void ComputeFlagsHC(u32 diff, u8& flags)
			{
				//Carry flag if bit 16 (unsigned overflow)
				if (diff & 0x10000)
					flags |= FLAG_C;
				else
					flags &= ~FLAG_C;

				//TODO: H flag (carry from bit 3 to 4)
			}
		}
	}
}