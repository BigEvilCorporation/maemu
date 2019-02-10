#include "StateEmu.h"

namespace app
{
	StateEmu::StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager)
		: ion::gamekit::State("emu", stateManager, resourceManager)
	{
		m_gui = nullptr;
		m_debuggerRegs = nullptr;
		m_debuggerState = DebuggerState::Break;
	}

	void StateEmu::OnEnterState()
	{
		//Create GUI
		//TODO
		m_gui = new ion::gui::GUI(ion::Vector2i(1024, 768));

		//Initialise emulator
		if (!m_masterSystem.LoadROM("roms/z80.bin"))
		{
			//Error
		}

		//Disassemble
		m_masterSystem.Disassemble(m_disassembly);

		//Create debugger
		m_debuggerRegs = new debug::WindowRegs(*m_gui, m_masterSystem.GetRegisters(), ion::Vector2i(20, 20), ion::Vector2i(200, 400));
		m_debuggerRAM = new debug::WindowMemory(*m_gui, m_masterSystem.GetRAM(), ion::Vector2i(250, 20), ion::Vector2i(600, 195));
		m_debuggerConsole = new debug::WindowConsole(*m_gui, m_masterSystem.GetConsole().GetBuffer(), ion::Vector2i(250, 230), ion::Vector2i(600, 195));
		m_debuggerDisassembly = new debug::WindowDisassembly(*m_gui, m_disassembly, ion::Vector2i(20, 430), ion::Vector2i(850, 300));

		m_gui->AddWindow(*m_debuggerConsole);
		m_gui->AddWindow(*m_debuggerDisassembly);
		m_gui->AddWindow(*m_debuggerRegs);
		m_gui->AddWindow(*m_debuggerRAM);
	}

	void StateEmu::OnLeaveState()
	{
		delete m_debuggerRegs;
		m_debuggerRegs = nullptr;

		delete m_gui;
		m_gui = nullptr;
	}

	void StateEmu::OnPauseState()
	{

	}

	void StateEmu::OnResumeState()
	{

	}

	bool StateEmu::Update(float deltaTime, ion::input::Keyboard* keyboard, ion::input::Mouse* mouse, ion::input::Gamepad* gamepad)
	{
		if (m_debuggerState == DebuggerState::Run)
		{
			//Update machine
			m_masterSystem.Update(deltaTime);
		}
		else if (m_debuggerState == DebuggerState::Break)
		{
			//Step if F10
			if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F10))
			{
				m_masterSystem.Update(deltaTime);
			}

			//Run if F5
			if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F5))
			{
				m_debuggerState = DebuggerState::Run;
			}
		}

		//Update debugger
		if (m_debuggerDisassembly)
		{
			m_debuggerDisassembly->HighlightAddress(m_masterSystem.GetRegisters().pc);
		}

		//Update UI
		m_gui->Update(deltaTime, keyboard, mouse, gamepad);

		return true;
	}

	void StateEmu::Render(ion::render::Renderer& renderer, const ion::render::Camera& camera, ion::render::Viewport& viewport)
	{
		//Render UI
		m_gui->Render(renderer, viewport);
	}
}