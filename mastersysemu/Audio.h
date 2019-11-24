#pragma once

#include <ion/audio/Engine.h>
#include <ion/audio/Buffer.h>
#include <ion/audio/Source.h>
#include <ion/audio/Voice.h>
#include <ion/audio/StreamDesc.h>

#include "Constants.h"

class AudioStreamDesc : public ion::audio::StreamDesc
{
public:
	virtual ion::audio::DataFormat GetEncodedFormat() const { return ion::audio::PCM16; }
	virtual ion::audio::DataFormat GetDecodedFormat() const { return ion::audio::PCM16; }

	virtual u32 GetNumChannels() const { return AUDIO_NUM_CHANNELS; }
	virtual u32 GetSampleRate() const { return AUDIO_SAMPLE_RATE_HZ; }
	virtual u32 GetBitsPerSample() const { return AUDIO_BUFFER_FORMAT_SIZE * 8; }
	virtual u32 GetBlockSize() const { return (GetNumChannels() * GetBitsPerSample()) / 8; }
	virtual u32 GetEncodedSizeBytes() const { return AUDIO_BUFFER_LEN_BYTES; }
	virtual u32 GetDecodedSizeBytes() const { return AUDIO_BUFFER_LEN_BYTES; }
	virtual u32 GetSizeSamples() const { return AUDIO_BUFFER_LEN_SAMPLES; }
};

class AudioSource : public ion::audio::Source
{
public:
	AudioSource();
	virtual bool OpenStream(OnStreamOpened const& onOpened);
	virtual void CloseStream(OnStreamClosed const& onClosed);
	virtual void RequestBuffer(ion::audio::SourceCallback& callback);

	void PushBuffer(const std::vector<emu::cpu::psg::SampleFormat>& buffer);

	u32 GetProducerIdx() const { return m_audioProducerBufferIdx; }
	u32 GetConsumerIdx() const { return m_audioConsumerBufferIdx; }

private:
	u32 m_audioProducerBufferIdx;
	u32 m_audioConsumerBufferIdx;
	ion::audio::Buffer* m_audioBuffers[AUDIO_NUM_BUFFERS];
	AudioStreamDesc m_audioStreamDesc;
};