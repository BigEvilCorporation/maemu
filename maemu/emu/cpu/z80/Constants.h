#pragma once

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			enum Interrupts
			{
				Z80_INTERRUPT_IFF1,
				Z80_INTERRUPT_IFF2,
			};

			static const int Z80_MAX_OPCODE_TABLE_SIZE = 0x100;
			static const int Z80_MAX_OPCODE_PARAMS = 4;
			static const int Z80_DEBUG_MAX_PC_HISTORY = 100;
		}
	}
}