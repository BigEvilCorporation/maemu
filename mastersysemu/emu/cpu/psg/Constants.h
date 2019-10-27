#pragma once

#include <ion/core/Types.h>

namespace emu
{
	namespace cpu
	{
		namespace psg
		{
			typedef u16 SampleFormat;

			static const int PSG_PORT_1 = 0x7E;
			static const int PSG_PORT_2 = 0x7F;

			static const int PSG_TONE_CHANNEL_COUNT = 3;

			static const int PSG_OUTPUT_BUFFER_SIZE = 1024 * 8;

			enum Channels
			{
				PSG_CHANNEL_TONE_1,
				PSG_CHANNEL_TONE_2,
				PSG_CHANNEL_TONE_3,
				PSG_CHANNEL_NOISE,

				PSG_CHANNEL_COUNT
			};
		}
	}
}