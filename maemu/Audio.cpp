#include "Audio.h"

#include <ion/core/debug/Debug.h>

AudioSource::AudioSource()
	: ion::audio::Source(ion::audio::Source::StreamingFeed)
{
	m_streamDesc = &m_audioStreamDesc;
	m_audioProducerBufferIdx = 0;

	//Create buffers
	const int bufferSize = emu::SMS_PSG_OUTPUT_BUFFER_SIZE_SAMPLES * sizeof(emu::cpu::psg::SampleFormat) * AUDIO_NUM_CHANNELS;

	for (int i = 0; i < AUDIO_NUM_BUFFERS; i++)
	{
		m_audioBuffers[i] = ion::audio::Buffer::Create(bufferSize);
	}

	//Lock first buffer
	m_audioBuffers[0]->WriteLock();
}

bool AudioSource::OpenStream(OnStreamOpened const& onOpened)
{
	return true;
}

void AudioSource::CloseStream(OnStreamClosed const& onClosed)
{
};

void AudioSource::PushBuffer(ion::audio::Voice& voice, const std::vector<emu::cpu::psg::SampleFormat>& buffer)
{
	if (buffer.size() > 0)
	{
		//Write to current buffer
		ion::audio::Buffer* writeBuffer = m_audioBuffers[m_audioProducerBufferIdx % AUDIO_NUM_BUFFERS];
		writeBuffer->Reset();
		writeBuffer->Add((const char*)buffer.data(), buffer.size() * sizeof(emu::cpu::psg::SampleFormat));
		writeBuffer->WriteUnlock();

		//Submit to voice
		voice.SubmitBuffer(*writeBuffer);

		//Advance buffer
		ion::thread::atomic::Increment(m_audioProducerBufferIdx);

		//Lock next buffer
		m_audioBuffers[m_audioProducerBufferIdx % AUDIO_NUM_BUFFERS]->WriteLock();
	}
}

void AudioSource::RequestBuffer(ion::audio::SourceCallback& callback)
{

}