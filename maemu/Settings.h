#pragma once

#include <ion/core/containers/FixedArray.h>
#include <ion/input/Keycodes.h>
#include <ion/input/Gamepad.h>

#include "emu/peripherals/Joypad.h"

struct Settings
{
	Settings()
	{
		keyboardMap[emu::peripherals::Joypad::BTN_UP] = ion::input::Keycode::UP;
		keyboardMap[emu::peripherals::Joypad::BTN_DOWN] = ion::input::Keycode::DOWN;
		keyboardMap[emu::peripherals::Joypad::BTN_LEFT] = ion::input::Keycode::LEFT;
		keyboardMap[emu::peripherals::Joypad::BTN_RIGHT] = ion::input::Keycode::RIGHT;
		keyboardMap[emu::peripherals::Joypad::BTN_A] = ion::input::Keycode::A;
		keyboardMap[emu::peripherals::Joypad::BTN_B] = ion::input::Keycode::S;

		gamepadMap[emu::peripherals::Joypad::BTN_UP] = ion::input::GamepadButtons::DPAD_UP;
		gamepadMap[emu::peripherals::Joypad::BTN_DOWN] = ion::input::GamepadButtons::DPAD_DOWN;
		gamepadMap[emu::peripherals::Joypad::BTN_LEFT] = ion::input::GamepadButtons::DPAD_LEFT;
		gamepadMap[emu::peripherals::Joypad::BTN_RIGHT] = ion::input::GamepadButtons::DPAD_RIGHT;
		gamepadMap[emu::peripherals::Joypad::BTN_A] = ion::input::GamepadButtons::BUTTON_X;
		gamepadMap[emu::peripherals::Joypad::BTN_B] = ion::input::GamepadButtons::BUTTON_A;
	}

	ion::FixedArray<ion::input::Keycode, emu::peripherals::Joypad::BTN_COUNT> keyboardMap;
	ion::FixedArray<ion::input::GamepadButtons, emu::peripherals::Joypad::BTN_COUNT> gamepadMap;
};
