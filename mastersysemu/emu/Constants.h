#pragma once

namespace emu
{
	//Audio
	static const int SMS_PSG_OUTPUT_BUFFER_SIZE = 1024 * 16;
	static const int SMS_PSG_OUTPUT_SAMPLE_RATE = 44100;

	//Timing
	static const int SMS_CYCLES_PER_SECOND_PAL = 3546894;
	static const int SMS_CYCLES_PER_SECOND_NTSC = 3579545;
	static const int SMS_CYCLES_PER_FRAME_PAL = 71364;
	static const int SMS_CYCLES_PER_FRAME_NTSC = 59736;
	static const int SMS_CYCLES_PER_SCANLINE = 228;
	static const int SMS_CYCLES_PER_PSG_STEP = 80;
	static const int SMS_CYCLES_PER_AUDIO_OUT = SMS_CYCLES_PER_SECOND_NTSC / SMS_PSG_OUTPUT_SAMPLE_RATE;

	//Address map
	static const int SMS_ADDR_ROM_START = 0x0000;
	static const int SMS_ADDR_ROM_END = 0xBFFF;

	static const int SMS_ADDR_RAM_START = 0xC000;
	static const int SMS_ADDR_RAM_END = 0xDFFF;

	//ROM mapper
	static const int SMS_MAPPER_START_ADDR = 0x400;
	static const int SMS_MAPPER_BANK_SIZE = 0x4000;
	static const int SMS_MAPPER_NUM_REGS = 4;
	static const int SMS_MAPPER_REG_STATE = 0xFFFC;
	static const int SMS_MAPPER_REG_BANK0 = 0xFFFD;
	static const int SMS_MAPPER_REG_BANK1 = 0xFFFE;
	static const int SMS_MAPPER_REG_BANK2 = 0xFFFF;

	//Port map
	static const int SMS_PORT_IO_CTRL = 0x3F;
	static const int SMS_PORT_IO_PORT1 = 0xDC;
	static const int SMS_PORT_IO_PORT2 = 0xDD;
	static const int SMS_PORT_SMS_SDSC_CTRL = 0xFC;
	static const int SMS_PORT_SMS_SDSC_DATA = 0xFD;
	static const int SMS_PORT_VDP_CTRL = 0xBF;
	static const int SMS_PORT_VDP_DATA = 0xBE;
	static const int SMS_PORT_VDP_VCOUNTER = 0x7E;
	static const int SMS_PORT_VDP_HCOUNTER = 0x7F;

	//Console
	static const int SMS_SDSC_CONSOLE_WIDTH = 80;
	static const int SMS_SDSC_CONSOLE_HEIGHT = 25;
}
