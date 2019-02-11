#pragma once

#include <ion/gui/GUI.h>
#include <ion/gui/Window.h>
#include <ion/gui/utils/MemoryViewer.h>

#include "emu/memory/Storage.h"

namespace debug
{
	class WindowMemory : public ion::gui::Window
	{
	public:
		WindowMemory(const std::string& name, ion::gui::GUI& gui, emu::memory::Storage& storage, const ion::Vector2i& position, const ion::Vector2i& size);
		~WindowMemory();

		virtual void Update(float deltaTime);

	private:
		ion::gui::GUI& m_gui;
		const emu::memory::Storage& m_storage;
		ion::gui::MemoryViewer m_memoryViewer;
	};
}