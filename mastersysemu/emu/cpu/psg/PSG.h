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

				SampleFormat GetOutputSample();

				const Registers& GetRegisters() const;

			private:
				static const s16 s_attenuationTable[];
				Registers m_registers;
				u8 m_timers[PSG_CHANNEL_COUNT];
				s8 m_polarities[PSG_CHANNEL_COUNT];
				u8 m_latchedChannel;
				u8 m_latchedRegister;
				SampleFormat m_outputSample;
			};
		}
	}
}