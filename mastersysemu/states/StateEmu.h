#pragma once

#include <ion/gamekit/StateManager.h>
#include <ion/gui/GUI.h>

#include "debugger/WindowConsole.h"
#include "debugger/WindowRegs.h"
#include "debugger/WindowMemory.h"

#include "emu/MasterSystem.h"

namespace app
{
	class StateEmu : public ion::gamekit::State
	{
	public:
		StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager);

		virtual void OnEnterState();
		virtual void OnLeaveState();
		virtual void OnPauseState();
		virtual void OnResumeState();

		virtual bool Update(float deltaTime, ion::input::Keyboard* keyboard, ion::input::Mouse* mouse, ion::input::Gamepad* gamepad);
		virtual void Render(ion::render::Renderer& renderer, const ion::render::Camera& camera, ion::render::Viewport& viewport);

	private:
		ion::gui::GUI* m_gui;
		debug::WindowConsole* m_debuggerConsole;
		debug::WindowRegs* m_debuggerRegs;
		debug::WindowMemory* m_debuggerRAM;

		//The machine
		emu::MasterSystem m_masterSystem;
	};
}
