#include "WindowMemory.h"

namespace debug
{
	WindowMemory::WindowMemory(const std::string& name, ion::gui::GUI& gui, emu::memory::Storage& storage, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window(name, position, size)
		, m_gui(gui)
		, m_memoryViewer(storage.GetMemory(), storage.GetMappedAddress())
	{
		AddWidget(m_memoryViewer);
	}

	WindowMemory::WindowMemory(const std::string& name, ion::gui::GUI& gui, emu::memory::Mapper& mapper, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window(name, position, size)
		, m_gui(gui)
		, m_memoryViewer(mapper.GetMemory(), 0)
	{
		AddWidget(m_memoryViewer);
	}

	WindowMemory::~WindowMemory()
	{

	}

	void WindowMemory::Update(float deltaTime)
	{
		Window::Update(deltaTime);
	}
}