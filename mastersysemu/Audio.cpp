#include "Audio.h"

#include <ion/core/debug/Debug.h>

AudioSource::AudioSource()
	: ion::audio::Source(ion::audio::Source::StreamingFeed)
{
	m_streamDesc = &m_audioStreamDesc;
	m_audioProducerBufferIdx = 0;
	m_audioConsumerBufferIdx = 0;

	//Create buffers and fill with silence
	for (int i = 0; i < AUDIO_NUM_BUFFERS; i++)
	{
		m_audioBuffers[i] = new ion::audio::Buffer(AUDIO_BUFFER_LEN_BYTES);
		m_audioBuffers[i]->Lock();
		m_audioBuffers[i]->Reserve(AUDIO_BUFFER_LEN_BYTES);
		m_audioBuffers[i]->Unlock();
	}

	//Init lead buffers
	m_audioProducerBufferIdx = AUDIO_NUM_LEAD_BUFFERS;
}

bool AudioSource::OpenStream(OnStreamOpened const& onOpened)
{
	return true;
}

void AudioSource::CloseStream(OnStreamClosed const& onClosed)
{
};

void AudioSource::PushBuffer(const std::vector<emu::cpu::psg::SampleFormat>& buffer)
{
	ion::audio::Buffer* writeBuffer = m_audioBuffers[m_audioProducerBufferIdx % AUDIO_NUM_BUFFERS];
	writeBuffer->Lock();
	writeBuffer->Reset();
	writeBuffer->Add((const char*)buffer.data(), buffer.size() * sizeof(emu::cpu::psg::SampleFormat));
	writeBuffer->Unlock();
	ion::thread::atomic::Increment(m_audioProducerBufferIdx);
}

void AudioSource::RequestBuffer(ion::audio::SourceCallback& callback)
{
	callback.SubmitBuffer(*m_audioBuffers[m_audioConsumerBufferIdx % AUDIO_NUM_BUFFERS]);
	ion::thread::atomic::Increment(m_audioConsumerBufferIdx);
	ion::debug::Assert(m_audioConsumerBufferIdx < m_audioProducerBufferIdx, "StateEmu::AudioSource::RequestBuffer() - Not enough data");
}