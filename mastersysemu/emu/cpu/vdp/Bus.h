#pragma once

#include "Constants.h"
#include "../../memory/MemoryController.h"
#include "../../ports/PortController.h"

namespace emu
{
	namespace cpu
	{
		namespace vdp
		{
			struct Bus
			{
				Bus(memory::Controller& controllerVRAM, memory::Controller& controllerCRAM, ports::Controller& ports)
					: memoryControllerVRAM(controllerVRAM)
					, memoryControllerCRAM(controllerCRAM)
					, portController(ports)
				{}

				memory::Controller& memoryControllerVRAM;
				memory::Controller& memoryControllerCRAM;
				ports::Controller& portController;
			};
		}
	}
}