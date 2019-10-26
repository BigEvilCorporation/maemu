#include "Joypad.h"

#include "../Constants.h"

namespace emu
{
	namespace peripherals
	{
		Joypad::Joypad(ports::Controller& portController)
		{
			portController.AddHandler(PORT_IO_CTRL, std::bind(&Joypad::ReadControl, this, std::placeholders::_1), std::bind(&Joypad::WriteControl, this, std::placeholders::_1, std::placeholders::_2));
			portController.AddHandler(PORT_IO_PORT1, std::bind(&Joypad::ReadPort1, this, std::placeholders::_1), std::bind(&Joypad::WritePort1, this, std::placeholders::_1, std::placeholders::_2));
			portController.AddHandler(PORT_IO_PORT2, std::bind(&Joypad::ReadPort2, this, std::placeholders::_1), std::bind(&Joypad::WritePort2, this, std::placeholders::_1, std::placeholders::_2));
		}

		u8 Joypad::ReadControl(u16 address)
		{
			return 0;
		}

		u8 Joypad::ReadPort1(u16 address)
		{
			return 0xFF;
		}

		u8 Joypad::ReadPort2(u16 address)
		{
			return 0xFF;
		}

		void Joypad::WriteControl(u16 address, u8 value)
		{

		}

		void Joypad::WritePort1(u16 address, u8 value)
		{

		}

		void Joypad::WritePort2(u16 address, u8 value)
		{

		}
	}
}