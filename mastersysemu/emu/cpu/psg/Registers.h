#pragma once

#include <ion/core/Types.h>

#include "Constants.h"

namespace emu
{
	namespace cpu
	{
		namespace psg
		{
			enum ChannelRegs
			{
				PSG_CHANNEL_REG_DATA,
				PSG_CHANNEL_REG_ATTENUATION,

				PSG_CHANNEL_REG_COUNT
			};

			struct Registers
			{
				u8 channels[PSG_CHANNEL_COUNT][PSG_CHANNEL_REG_COUNT];
			};

			struct RegisterWriteByte
			{
				union
				{
					struct
					{
						u8 data : 4;
						u8 dataType : 1;
						u8 channel : 2;
						u8 latch : 1;
					} latched;

					struct
					{
						u8 data : 6;
						u8 unused : 1;
						u8 latch : 1;
					} unlatched;
				};
			};
		}
	}
}