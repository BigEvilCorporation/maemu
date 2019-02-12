#pragma once

#include <ion/core/Types.h>

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			static const int Z80_INT_NMI_ADDRESS = 0x0066;
			static const int Z80_INT_MODE2_ADDRESS = 0x0038;

			enum InterruptMode
			{
				Z80_INT_MODE0,
				Z80_INT_MODE1,
				Z80_INT_MODE2,
			};
		}
	}
}