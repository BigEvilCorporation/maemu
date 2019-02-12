#include "WindowRegsZ80.h"

#include <ion/core/utils/STL.h>

namespace debug
{
	WindowRegsZ80::WindowRegsZ80(ion::gui::GUI& gui, const emu::cpu::z80::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Z80 Registers", position, size)
		, m_gui(gui)
		, m_regs(regs)
	{
		for (int i = 0; i < 4; i++)
		{
			AddWidget(m_textBoxes.main[i]);
			m_textBoxes.alt[i].SetArrangement(ion::gui::Widget::Arrangement::Horizontal);
			AddWidget(m_textBoxes.alt[i]);
		}

		AddWidget(m_textBoxes.ix);
		AddWidget(m_textBoxes.iy);
		AddWidget(m_textBoxes.pc);
		AddWidget(m_textBoxes.sp);
		AddWidget(m_textBoxes.i);
		AddWidget(m_textBoxes.r);
		AddWidget(m_textBoxes.im);
		AddWidget(m_textBoxes.iff1);
		AddWidget(m_textBoxes.iff2);
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
		SetRegText16(m_textBoxes.main[0], "AF", m_regs.main.af);
		SetRegText16(m_textBoxes.main[1], "BC", m_regs.main.bc);
		SetRegText16(m_textBoxes.main[2], "DE", m_regs.main.de);
		SetRegText16(m_textBoxes.main[3], "HL", m_regs.main.hl);

		SetRegText16(m_textBoxes.alt[0], "AF'", m_regs.alt.af);
		SetRegText16(m_textBoxes.alt[1], "BC'", m_regs.alt.bc);
		SetRegText16(m_textBoxes.alt[2], "DE'", m_regs.alt.de);
		SetRegText16(m_textBoxes.alt[3], "HL'", m_regs.alt.hl);

		SetRegText16(m_textBoxes.pc, "PC", m_regs.pc);
		SetRegText16(m_textBoxes.sp, "SP", m_regs.sp);
		SetRegText16(m_textBoxes.ix, "IX", m_regs.ix);
		SetRegText16(m_textBoxes.iy, "IY", m_regs.iy);
		SetRegText8(m_textBoxes.i, "I", m_regs.i);
		SetRegText8(m_textBoxes.r, "R", m_regs.r);

		SetRegText8(m_textBoxes.im, "IM", m_regs.internal.im);
		SetRegText8(m_textBoxes.iff1, "IFF1", m_regs.internal.iff1);
		SetRegText8(m_textBoxes.iff2, "IFF2", m_regs.internal.iff2);
	}

	void WindowRegsZ80::SetRegText8(ion::gui::TextBox& text, const std::string& name, u8 value)
	{
		std::stringstream stream;
		stream << name << ": " << SSTREAM_HEX2(value);
		text.SetText(stream.str());
	}

	void WindowRegsZ80::SetRegText16(ion::gui::TextBox& text, const std::string& name, u16 value)
	{
		std::stringstream stream;
		stream << name << ": " << SSTREAM_HEX4(value);
		text.SetText(stream.str());
	}
}
