#pragma once

namespace emu
{
	//Timing
	static const int MS_CYCLES_PER_SCANLINE = 3420;

	//Address map
	static const int ADDR_ROM_START = 0x0000;
	static const int ADDR_ROM_END = 0xBFFF;

	static const int ADDR_RAM_START = 0xC000;
	static const int ADDR_RAM_END = 0xDFFF;

	//ROM mapper
	static const int MAPPER_BANK_SIZE = 0x4000;
	static const int MAPPER_NUM_REGS = 4;
	static const int MAPPER_REG_STATE = 0xFFFC;
	static const int MAPPER_REG_BANK0 = 0xFFFD;
	static const int MAPPER_REG_BANK1 = 0xFFFE;
	static const int MAPPER_REG_BANK2 = 0xFFFF;

	//Port map
	static const int PORT_IO_CTRL = 0x3F;
	static const int PORT_IO_PORT1 = 0xDC;
	static const int PORT_IO_PORT2 = 0xDD;
	static const int PORT_SDSC_CTRL = 0xFC;
	static const int PORT_SDSC_DATA = 0xFD;
	static const int PORT_VDP_CTRL = 0xBF;
	static const int PORT_VDP_DATA = 0xBE;
	static const int PORT_VDP_VCOUNTER = 0x7E;
	static const int PORT_VDP_HCOUNTER = 0x7F;

	//Console
	static const int SDSC_CONSOLE_WIDTH = 80;
	static const int SDSC_CONSOLE_HEIGHT = 25;
}
