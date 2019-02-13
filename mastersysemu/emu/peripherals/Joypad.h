#pragma once

#include "../ports/PortController.h"

namespace emu
{
	namespace peripherals
	{
		class Joypad
		{
		public:
			Joypad(ports::Controller& portController);

			u8 ReadControl(u16 address);
			u8 ReadPort1(u16 address);
			u8 ReadPort2(u16 address);

			void WriteControl(u16 address, u8 value);
			void WritePort1(u16 address, u8 value);
			void WritePort2(u16 address, u8 value);
		};
	}
}