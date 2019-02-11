#include "WindowRegsVDP.h"

#include <ion/core/utils/STL.h>

namespace debug
{
	WindowRegsVDP::WindowRegsVDP(ion::gui::GUI& gui, const emu::cpu::vdp::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("VDP Registers", position, size)
		, m_gui(gui)
		, m_regs(regs)
	{
		for (int i = 0; i < emu::cpu::vdp::VDP_NUM_REGISTERS; i++)
		{
			AddWidget(m_textBoxes[i]);
		}
	}

	WindowRegsVDP::~WindowRegsVDP()
	{

	}

	void WindowRegsVDP::Update(float deltaTime)
	{
		UpdateRegs();
		Window::Update(deltaTime);
	}

	void WindowRegsVDP::UpdateRegs()
	{
		for (int i = 0; i < emu::cpu::vdp::VDP_NUM_REGISTERS; i++)
		{
			SetRegText8(m_textBoxes[i], i, m_regs[i]);
		}
	}

	void WindowRegsVDP::SetRegText8(ion::gui::TextBox& text, u8 index, u8 value)
	{
		std::stringstream stream;
		stream << SSTREAM_HEX2(index) << ":" << SSTREAM_HEX2(value);
		text.SetText(stream.str());
	}
}
