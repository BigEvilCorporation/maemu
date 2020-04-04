#pragma once

#include "emu/Constants.h"
#include "emu/cpu/psg/Constants.h"

#define EMU_INCLUDE_AUDIO		1
#define EMU_INCLUDE_DEBUGGER	0

static const int AUDIO_NUM_CHANNELS = 1;
static const int AUDIO_NUM_BUFFERS = 2;

#if !EMU_INCLUDE_AUDIO
//Large default delta for faster ZEXALL testing
static const float EMU_DEFAULT_STEP_DELTA = 10.0f;
#endif