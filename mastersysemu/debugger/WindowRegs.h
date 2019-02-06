#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/Button.h>
#include <ion/gui/CheckBox.h>
#include <ion/gui/ComboBox.h>
#include <ion/gui/TextBox.h>

#include "emu/cpu/z80/Registers.h"

namespace debug
{
	class WindowRegs : public ion::gui::Window
	{
	public:
		WindowRegs(ion::gui::GUI& gui, const emu::cpu::z80::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowRegs();

		virtual void Update(float deltaTime);

	private:
		void UpdateRegs();
		void SetRegText8(ion::gui::TextBox& text, const std::string& name, u8 value);
		void SetRegText16(ion::gui::TextBox& text, const std::string& name, u16 value);

		ion::gui::GUI& m_gui;
		const emu::cpu::z80::Registers& m_regs;

		struct
		{
			ion::gui::TextBox main[8];
			ion::gui::TextBox alt[8];
			ion::gui::TextBox pc;
			ion::gui::TextBox sp;
			ion::gui::TextBox ix;
			ion::gui::TextBox iy;
			ion::gui::TextBox i;
			ion::gui::TextBox r;
		} m_textBoxes;
	};

}