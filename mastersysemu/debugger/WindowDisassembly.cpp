#include "WindowDisassembly.h"

namespace debug
{
	WindowDisassembly::WindowDisassembly(ion::gui::GUI& gui, const std::vector<emu::cpu::z80::disassembler::Instruction>& disassembly, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Disassembly", position, size)
		, m_gui(gui)
		, m_disassembly(disassembly)
	{
		m_disassemblyText = emu::cpu::z80::disassembler::ToText(disassembly);
		m_textEditor.SetText(m_disassemblyText);
		AddWidget(m_textEditor);
	}

	WindowDisassembly::~WindowDisassembly()
	{

	}

	void WindowDisassembly::HighlightAddress(u16 address)
	{
		int line = 0;

		for (int i = 0; i < m_disassembly.size(); i++)
		{
			if (m_disassembly[i].address == address)
			{
				line = i;
				break;
			}
		}

		m_textEditor.HighlightLine(line);
	}

	void WindowDisassembly::Update(float deltaTime)
	{
		Window::Update(deltaTime);
	}
}