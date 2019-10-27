#pragma once

#include "Constants.h"
#include "Registers.h"
#include "../../ports/PortController.h"

namespace emu
{
	namespace cpu
	{
		namespace psg
		{
			class PSG
			{
			public:
				PSG(ports::Controller& ports);

				void Reset();
				void Step();
				void WriteReg(u16 address, u8 value);

				void GetOutput(std::vector<SampleFormat>& data);

			private:
				u8 m_registers[PSG_CHANNEL_COUNT][PSG_CHANNEL_REG_COUNT];
				u8 m_timers[PSG_CHANNEL_COUNT];
				s8 m_polarities[PSG_CHANNEL_COUNT];
				u8 m_latchedChannel;
				u8 m_latchedRegister;

				SampleFormat m_outputBuffer[PSG_OUTPUT_BUFFER_SIZE];
				u32 m_outputBufferPtr;
			};
		}
	}
}