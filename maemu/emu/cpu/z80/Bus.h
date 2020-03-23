#pragma once

#include "../../memory/MemoryController.h"
#include "../../ports/PortController.h"

namespace emu
{
	namespace cpu
	{
		namespace z80
		{
			struct Bus
			{
				Bus(memory::Controller& memory, ports::Controller& ports)
					: memoryController(memory)
					, portController(ports)
				{}

				memory::Controller& memoryController;
				ports::Controller& portController;
			};
		}
	}
}