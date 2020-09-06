#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/Button.h>
#include <ion/gui/CheckBox.h>
#include <ion/gui/ComboBox.h>
#include <ion/gui/TextBox.h>

#include "emu/cpu/psg/Registers.h"
#include "emu/cpu/psg/Constants.h"

#include "Audio.h"

namespace debug
{
	class WindowAudio : public ion::gui::Window
	{
	public:
		WindowAudio(ion::gui::GUI& gui, const AudioSource& audioSource, const emu::cpu::psg::Registers& regs, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowAudio();

		virtual void Update(float deltaTime);

	private:
		void UpdateRegs();
		void UpdateBuffers();
		void SetRegText(ion::gui::TextBox& text, const std::string& name, u32 value);
		void SetRegText8(ion::gui::TextBox& text, const std::string& name, u8 value);
		void SetRegText16(ion::gui::TextBox& text, const std::string& name, u16 value);

		ion::gui::GUI& m_gui;
		const emu::cpu::psg::Registers& m_regs;
		const AudioSource& m_audioSource;

		struct
		{
			struct
			{
				ion::gui::TextBox registers[emu::cpu::psg::PSG_CHANNEL_REG_COUNT];
			} channels[emu::cpu::psg::PSG_CHANNEL_COUNT];
			
			ion::gui::TextBox buffersSubmitted;
		} m_textBoxes;
	};
}