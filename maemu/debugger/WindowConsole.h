#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/TextBox.h>

#include <string>

namespace debug
{
	class WindowConsole : public ion::gui::Window
	{
	public:
		WindowConsole(ion::gui::GUI& gui, const std::string& text, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowConsole();

		virtual void Update(float deltaTime);

	private:
		ion::gui::TextBox m_textBox;
		const std::string& m_text;
	};
}