#pragma once

#include "Constants.h"

#include <ion/core/Types.h>
#include <ion/core/containers/FixedArray.h>

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			typedef ion::FixedArray<u8, VDP_NUM_REGISTERS> Registers;

			enum VDPRegs
			{
				VDP_REG_0_MODE_CONTROL_1			= 0x0,
				VDP_REG_1_MODE_CONTROL_2			= 0x1,
				VDP_REG_2_NAME_TABLE_ADDR			= 0x2,
				VDP_REG_3_COLOUR_TABLE_ADDR			= 0x3,
				VDP_REG_4_PATTERN_TABLE_ADDR		= 0x4,
				VDP_REG_5_SPRITE_ATTR_TABLE_ADDR	= 0x5,
				VDP_REG_6_SPRITE_PATTERN_TABLE_ADDR	= 0x6,
				VDP_REG_7_BACKDROP_COLOUR			= 0x7,
				VDP_REG_8_SCROLL_X					= 0x8,
				VDP_REG_9_SCROLL_Y					= 0x9,
				VDP_REG_A_LINE_COUNTER				= 0xA
			};
		}
	}
}