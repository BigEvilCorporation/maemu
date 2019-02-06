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
				static void SetFlagsZCS(u16 diff, u8& flags)
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
			}
		}
	}
}