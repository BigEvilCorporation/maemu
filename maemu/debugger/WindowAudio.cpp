#include "WindowAudio.h"

#include <ion/core/utils/STL.h>

namespace debug
{
	WindowAudio::WindowAudio(ion::gui::GUI& gui, const AudioSource& audioSource, const emu::cpu::psg::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Audio", position, size)
		, m_gui(gui)
		, m_regs(regs)
		, m_audioSource(audioSource)
	{
		for (int i = 0; i < emu::cpu::psg::PSG_CHANNEL_COUNT; i++)
		{
			for (int j = 0; j < emu::cpu::psg::PSG_CHANNEL_REG_COUNT; j++)
			{
				AddWidget(m_textBoxes.channels[i].registers[j]);
			}
		}

		AddWidget(m_textBoxes.buffersSubmitted);
	}

	WindowAudio::~WindowAudio()
	{

	}

	void WindowAudio::Update(float deltaTime)
	{
		UpdateRegs();
		UpdateBuffers();
		Window::Update(deltaTime);
	}

	void WindowAudio::UpdateRegs()
	{
		for (int i = 0; i < emu::cpu::psg::PSG_CHANNEL_COUNT; i++)
		{
			for (int j = 0; j < emu::cpu::psg::PSG_CHANNEL_REG_COUNT; j++)
			{
				std::string label = "Chan " + std::to_string(i) + " reg " + std::to_string(j) + ": ";
				SetRegText16(m_textBoxes.channels[i].registers[j], label, m_regs.channels[i][j]);
			}
		}
	}

	void WindowAudio::UpdateBuffers()
	{
		SetRegText(m_textBoxes.buffersSubmitted, "Buffers submitted:", m_audioSource.GetProducerIdx());
	}

	void WindowAudio::SetRegText(ion::gui::TextBox& text, const std::string& name, u32 value)
	{
		std::stringstream stream;
		stream << name << ": " << value;
		text.SetText(stream.str());
	}

	void WindowAudio::SetRegText8(ion::gui::TextBox& text, const std::string& name, u8 value)
	{
		std::stringstream stream;
		stream << name << ": " << SSTREAM_HEX2(value);
		text.SetText(stream.str());
	}

	void WindowAudio::SetRegText16(ion::gui::TextBox& text, const std::string& name, u16 value)
	{
		std::stringstream stream;
		stream << name << ": " << SSTREAM_HEX4(value);
		text.SetText(stream.str());
	}
}
