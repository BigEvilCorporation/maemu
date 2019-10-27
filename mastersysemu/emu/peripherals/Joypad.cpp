#include "Joypad.h"

#include "../Constants.h"

namespace emu
{
	namespace peripherals
	{
		const u8 Joypad::s_emulatorButtonBits[Joypad::BTN_COUNT] =
		{
			(1 << 0),	// Up
			(1 << 1),	// Down
			(1 << 2),	// Left
			(1 << 3),	// Right
			(1 << 4),	// A
			(1 << 5),	// B
		};

		Joypad::Joypad(ports::Controller& portController)
		{
			portController.AddHandler(PORT_IO_CTRL, std::bind(&Joypad::ReadControl, this, std::placeholders::_1), std::bind(&Joypad::WriteControl, this, std::placeholders::_1, std::placeholders::_2));
			portController.AddHandler(PORT_IO_PORT1, std::bind(&Joypad::ReadPort1, this, std::placeholders::_1), std::bind(&Joypad::WritePort1, this, std::placeholders::_1, std::placeholders::_2));
			portController.AddHandler(PORT_IO_PORT2, std::bind(&Joypad::ReadPort2, this, std::placeholders::_1), std::bind(&Joypad::WritePort2, this, std::placeholders::_1, std::placeholders::_2));

			for (int i = 0; i < JOYPAD_COUNT; i++)
			{
				m_states[i] = 0xFF;
			}
		}

		void Joypad::SetButtonState(PadIndex joypad, Button button, bool state)
		{
			if (state)
				m_states[joypad] &= ~s_emulatorButtonBits[button];
			else
				m_states[joypad] |= s_emulatorButtonBits[button];
		}

		u8 Joypad::ReadControl(u16 address)
		{
			return 0;
		}

		u8 Joypad::ReadPort1(u16 address)
		{
			return m_states[JOYPAD_1];
		}

		u8 Joypad::ReadPort2(u16 address)
		{
			return m_states[JOYPAD_2];
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