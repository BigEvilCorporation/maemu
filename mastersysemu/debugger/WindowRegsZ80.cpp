#include "WindowRegsZ80.h"

#include <ion/core/utils/STL.h>

namespace debug
{
	WindowRegsZ80::WindowRegsZ80(ion::gui::GUI& gui, const emu::cpu::z80::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Z80 Registers", position, size)
		, m_gui(gui)
		, m_regs(regs)
	{
		for (int i = 0; i < 8; i += 2)
		{
			AddWidget(m_textBoxes.main[i]);
			m_textBoxes.main[i+1].SetArrangement(ion::gui::Widget::Arrangement::Horizontal);
			AddWidget(m_textBoxes.main[i+1]);
		}

		for (int i = 0; i < 8; i += 2)
		{
			AddWidget(m_textBoxes.alt[i]);
			m_textBoxes.alt[i+1].SetArrangement(ion::gui::Widget::Arrangement::Horizontal);
			AddWidget(m_textBoxes.alt[i + 1]);
		}

		AddWidget(m_textBoxes.ix);
		AddWidget(m_textBoxes.iy);
		AddWidget(m_textBoxes.pc);
		AddWidget(m_textBoxes.sp);
		AddWidget(m_textBoxes.i);
		AddWidget(m_textBoxes.r);
	}

	WindowRegsZ80::~WindowRegsZ80()
	{

	}

	void WindowRegsZ80::Update(float deltaTime)
	{
		UpdateRegs();
		Window::Update(deltaTime);
	}

	void WindowRegsZ80::UpdateRegs()
	{
		SetRegText8(m_textBoxes.main[0], "A", m_regs.main.a);
		SetRegText8(m_textBoxes.main[1], "F", m_regs.main.f);
		SetRegText8(m_textBoxes.main[2], "B", m_regs.main.b);
		SetRegText8(m_textBoxes.main[3], "C", m_regs.main.c);
		SetRegText8(m_textBoxes.main[4], "D", m_regs.main.d);
		SetRegText8(m_textBoxes.main[5], "E", m_regs.main.e);
		SetRegText8(m_textBoxes.main[6], "H", m_regs.main.h);
		SetRegText8(m_textBoxes.main[7], "L", m_regs.main.l);

		SetRegText8(m_textBoxes.alt[0], "A'", m_regs.alt.a);
		SetRegText8(m_textBoxes.alt[1], "F'", m_regs.alt.f);
		SetRegText8(m_textBoxes.alt[2], "B'", m_regs.alt.b);
		SetRegText8(m_textBoxes.alt[3], "C'", m_regs.alt.c);
		SetRegText8(m_textBoxes.alt[4], "D'", m_regs.alt.d);
		SetRegText8(m_textBoxes.alt[5], "E'", m_regs.alt.e);
		SetRegText8(m_textBoxes.alt[6], "H'", m_regs.alt.h);
		SetRegText8(m_textBoxes.alt[7], "L'", m_regs.alt.l);

		SetRegText16(m_textBoxes.pc, "PC", m_regs.pc);
		SetRegText16(m_textBoxes.sp, "SP", m_regs.sp);
		SetRegText16(m_textBoxes.ix, "IX", m_regs.ix);
		SetRegText16(m_textBoxes.iy, "IY", m_regs.iy);
		SetRegText8(m_textBoxes.i, "I", m_regs.i);
		SetRegText8(m_textBoxes.r, "R", m_regs.r);
	}

	void WindowRegsZ80::SetRegText8(ion::gui::TextBox& text, const std::string& name, u8 value)
	{
		std::stringstream stream;
		stream << name << ": 0x" << SSTREAM_HEX2(value);
		text.SetText(stream.str());
	}

	void WindowRegsZ80::SetRegText16(ion::gui::TextBox& text, const std::string& name, u16 value)
	{
		std::stringstream stream;
		stream << name << ": 0x" << SSTREAM_HEX4(value);
		text.SetText(stream.str());
	}
}
