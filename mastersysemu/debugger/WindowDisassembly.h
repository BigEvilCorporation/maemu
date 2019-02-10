#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/utils/TextEditor.h>

#include <emu/cpu/z80/Disassembler.h>

namespace debug
{
	class WindowDisassembly : public ion::gui::Window
	{
	public:
		WindowDisassembly(ion::gui::GUI& gui, const std::vector<emu::cpu::z80::disassembler::Instruction>& disassembly, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowDisassembly();

		void HighlightAddress(u16 address);

		virtual void Update(float deltaTime);

	private:
		ion::gui::GUI& m_gui;
		ion::gui::TextEditor m_textEditor;
		const std::vector<emu::cpu::z80::disassembler::Instruction>& m_disassembly;
		std::string m_disassemblyText;
	};
}