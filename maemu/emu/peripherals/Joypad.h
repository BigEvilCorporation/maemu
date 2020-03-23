#pragma once

#include "../ports/PortController.h"

namespace emu
{
	namespace peripherals
	{
		class Joypad
		{
		public:
			enum PadIndex
			{
				JOYPAD_1,
				JOYPAD_2,
				JOYPAD_COUNT
			};

			enum Button
			{
				BTN_UP = 0,
				BTN_DOWN,
				BTN_LEFT,
				BTN_RIGHT,
				BTN_A,
				BTN_B,
				BTN_COUNT
			};

			Joypad(ports::Controller& portController);

			void SetButtonState(PadIndex joypad, Button button, bool state);

			u8 ReadControl(u16 address);
			u8 ReadPort1(u16 address);
			u8 ReadPort2(u16 address);

			void WriteControl(u16 address, u8 value);
			void WritePort1(u16 address, u8 value);
			void WritePort2(u16 address, u8 value);

		private:
			static const u8 s_emulatorButtonBits[BTN_COUNT];
			u8 m_states[JOYPAD_COUNT];
		};
	}
}