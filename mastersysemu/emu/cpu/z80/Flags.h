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
		}
	}
}