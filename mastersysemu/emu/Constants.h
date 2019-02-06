#pragma once

namespace emu
{
	//Address map
	static const int ADDR_ROM_START = 0x0000;
	static const int ADDR_ROM_END = 0xBFFF;

	static const int ADDR_RAM_START = 0xC000;
	static const int ADDR_RAM_END = 0xDFFF;

	//Port map
	static const int PORT_SDSC_CONTROL = 0xFC;
	static const int PORT_SDSC_DATA = 0xFD;

	//Console
	static const int SDSC_CONSOLE_WIDTH = 80;
	static const int SDSC_CONSOLE_HEIGHT = 25;
}
