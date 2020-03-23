#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/Button.h>
#include <ion/gui/CheckBox.h>
#include <ion/gui/ComboBox.h>
#include <ion/gui/TextBox.h>

#include "emu/cpu/vdp/Registers.h"
#include "emu/cpu/vdp/Constants.h"

namespace debug
{
	class WindowRegsVDP : public ion::gui::Window
	{
	public:
		WindowRegsVDP(ion::gui::GUI& gui, const emu::cpu::vdp::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowRegsVDP();

		virtual void Update(float deltaTime);

	private:
		void UpdateRegs();
		void SetRegText8(ion::gui::TextBox& text, u8 index, u8 value);

		ion::gui::GUI& m_gui;
		const emu::cpu::vdp::Registers& m_regs;

		ion::gui::TextBox m_textBoxes[emu::cpu::vdp::VDP_NUM_REGISTERS];
	};

}