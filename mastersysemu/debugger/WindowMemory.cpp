#include "WindowMemory.h"

namespace debug
{
	WindowMemory::WindowMemory(ion::gui::GUI& gui, emu::memory::Storage& storage, const ion::Vector2i& position, const ion::Vector2i& size)
		: ion::gui::Window("Memory", position, size)
		, m_gui(gui)
		, m_storage(storage)
		, m_memoryViewer(storage.GetMemory(), storage.GetMappedAddress())
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