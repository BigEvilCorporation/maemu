#pragma once

#include "../Flags.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			namespace opcodes
			{
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
			}
		}
	}
}