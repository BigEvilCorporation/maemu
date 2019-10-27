#include "PSG.h"
#include "Registers.h"

#include <ion/core/memory/Memory.h>

namespace emu
{
	namespace cpu
	{
		namespace psg
		{
#pragma optimize("",off)
			PSG::PSG(ports::Controller& ports)
			{
				ports.AddHandler(PSG_PORT_1, nullptr, std::bind(&PSG::WriteReg, this, std::placeholders::_1, std::placeholders::_2));
				ports.AddHandler(PSG_PORT_2, nullptr, std::bind(&PSG::WriteReg, this, std::placeholders::_1, std::placeholders::_2));
			}

			void PSG::Reset()
			{
				for (int i = 0; i < PSG_CHANNEL_COUNT; i++)
				{
					m_registers[i][PSG_CHANNEL_REG_ATTENUATION] = 0xFF;
					m_registers[i][PSG_CHANNEL_REG_DATA] = 0x00;
					m_timers[i] = 0;
					m_polarities[i] = -1;
				}

				m_latchedChannel = 0;
				m_latchedRegister = 0;
				m_outputBufferPtr = 0;

				ion::memory::MemSet(m_outputBuffer, 0, PSG_OUTPUT_BUFFER_SIZE * sizeof(SampleFormat));
			}

			void PSG::Step()
			{
				if (m_outputBufferPtr < PSG_OUTPUT_BUFFER_SIZE)
				{
					u8 outputByte = 0;

					for (int i = 0; i < PSG_TONE_CHANNEL_COUNT; i++)
					{
						//If channel enabled
						if (m_timers[i] > 0)
						{
							//Decrement channel counter
							if (--m_timers[i] == 0)
							{
								//Depleted, reset timer and revert square wave polarity
								m_timers[i] = m_registers[i][PSG_CHANNEL_REG_DATA];
								m_polarities[i] *= -1;
							}

							//Mix channel output byte
							outputByte += (m_polarities[i] * (256 - m_registers[i][PSG_CHANNEL_REG_ATTENUATION])) / PSG_CHANNEL_COUNT;
						}
					}

					static const float outputScalar = (float)std::numeric_limits<SampleFormat>::max() / 256.0f;
					m_outputBuffer[m_outputBufferPtr++] = (SampleFormat)(outputByte * outputScalar);
				}
				else
				{
					m_outputBufferPtr = 0;
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
					m_registers[m_latchedChannel][m_latchedRegister] = dataByte.latched.data;
				}
				else
				{
					//Data only
					m_registers[m_latchedChannel][m_latchedRegister] |= dataByte.unlatched.data;
				}

				//If data, reset timer
				if (m_latchedRegister == PSG_CHANNEL_REG_DATA)
				{
					m_timers[m_latchedChannel] = m_registers[m_latchedChannel][m_latchedRegister];
				}
			}

			void PSG::GetOutput(std::vector<SampleFormat>& data)
			{
				data.resize(m_outputBufferPtr);
				ion::memory::MemCopy(data.data(), m_outputBuffer, m_outputBufferPtr * sizeof(SampleFormat));
				ion::memory::MemSet(m_outputBuffer, 0, PSG_OUTPUT_BUFFER_SIZE * sizeof(SampleFormat));
				m_outputBufferPtr = 0;
			}
#pragma optimize("",on)
		}
	}
}