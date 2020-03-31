#pragma once

#include "emu/Constants.h"
#include "emu/cpu/psg/Constants.h"

#define EMU_INCLUDE_DEBUGGER 1

static const int AUDIO_NUM_CHANNELS = 1;
static const int AUDIO_NUM_LEAD_BUFFERS = 3;
static const int AUDIO_NUM_BUFFERS = 3;
static const int AUDIO_BUFFER_FORMAT_SIZE = sizeof(emu::cpu::psg::SampleFormat);
static const int AUDIO_SAMPLE_RATE_HZ = emu::SMS_PSG_OUTPUT_SAMPLE_RATE;
static const int AUDIO_BUFFER_LEN_BYTES = (AUDIO_SAMPLE_RATE_HZ / 60) * AUDIO_BUFFER_FORMAT_SIZE * AUDIO_NUM_CHANNELS;
static const int AUDIO_BUFFER_LEN_SAMPLES = emu::SMS_PSG_OUTPUT_BUFFER_SIZE / AUDIO_BUFFER_FORMAT_SIZE;