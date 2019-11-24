#include "PSG.h"
#include "Registers.h"

#include <ion/core/memory/Memory.h>
#include <ion/maths/Maths.h>

namespace emu
{
	namespace cpu
	{
		namespace psg
		{
#pragma optimize("",off)

			const s16 PSG::s_attenuationTable[] =
			{
				32767,
				26028,
				20675,
				16422,
				13045,
				10362,
				8231,
				6568,
				5193,
				4125,
				3277,
				2603,
				2067,
				1642,
				1304,
				0
			};

			PSG::PSG(ports::Controller& ports)
			{
				ports.AddHandler(PSG_SMS_PORT_1, nullptr, std::bind(&PSG::WriteReg, this, std::placeholders::_1, std::placeholders::_2));
				ports.AddHandler(PSG_SMS_PORT_2, nullptr, std::bind(&PSG::WriteReg, this, std::placeholders::_1, std::placeholders::_2));
			}

			void PSG::Reset()
			{
				for (int i = 0; i < PSG_CHANNEL_COUNT; i++)
				{
					m_registers.channels[i][PSG_CHANNEL_REG_ATTENUATION] = 0xFF;
					m_registers.channels[i][PSG_CHANNEL_REG_DATA] = 0x00;
					m_timers[i] = 0;
					m_polarities[i] = -1;
				}

				m_latchedChannel = 0;
				m_latchedRegister = 0;
				m_outputSample = 0;
			}

			void PSG::Step()
			{
				m_outputSample = 0;

				for (int i = 0; i < PSG_TONE_CHANNEL_COUNT; i++)
				{
					//If channel enabled
					if (m_timers[i] > 0)
					{
						//Decrement channel counter
						if (--m_timers[i] == 0)
						{
							//Depleted, reset timer and revert square wave polarity
							m_timers[i] = m_registers.channels[i][PSG_CHANNEL_REG_DATA];
							m_polarities[i] *= -1;
						}

						//Mix channel output byte
						static const float outputScalar = (float)std::numeric_limits<SampleFormat>::max() / 256.0f;
						m_outputSample += ion::maths::Round(((m_polarities[i] * s_attenuationTable[m_registers.channels[i][PSG_CHANNEL_REG_ATTENUATION]]) / PSG_CHANNEL_COUNT) * outputScalar);
					}
				}
			}

			void PSG::WriteReg(u16 address, u8 value)
			{
				RegisterWriteByte& dataByte = (RegisterWriteByte&)value;

				if (dataByte.latched.latch)
				{
					//Command+data byte
					m_latchedChannel = dataByte.latched.channel;
					m_latchedRegister = dataByte.latched.dataType;
					m_registers.channels[m_latchedChannel][m_latchedRegister] = dataByte.latched.data;
				}
				else
				{
					//Data only
					m_registers.channels[m_latchedChannel][m_latchedRegister] |= dataByte.unlatched.data;
				}

				//If data, reset timer
				if (m_latchedRegister == PSG_CHANNEL_REG_DATA)
				{
					m_timers[m_latchedChannel] = m_registers.channels[m_latchedChannel][m_latchedRegister];
				}
			}

			SampleFormat PSG::GetOutputSample()
			{
				return m_outputSample;
			}

			const Registers& PSG::GetRegisters() const
			{
				return m_registers;
			}
#pragma optimize("",on)
		}
	}
}