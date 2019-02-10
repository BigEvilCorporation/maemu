#pragma once

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			enum Flags
			{
				VDP_STATUS_INTERRUPT		= (1 << 7),
				VDP_STATUS_SPRITE_OVERFLOW	= (1 << 6),
				VDP_STATUS_SPRITE_COLLISION	= (1 << 5)
			};
		}
	}
}