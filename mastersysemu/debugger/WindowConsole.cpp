#include "WindowConsole.h"

namespace debug
{
	WindowConsole::WindowConsole(ion::gui::GUI& gui, const std::string& text, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Console", position, size)
		, m_text(text)
	{
		AddWidget(m_textBox);
	}

	WindowConsole::~WindowConsole()
	{

	}

	void WindowConsole::Update(float deltaTime)
	{
		m_textBox.SetText(m_text);
		Window::Update(deltaTime);
	}
}