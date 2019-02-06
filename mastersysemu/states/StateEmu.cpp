#include "StateEmu.h"

namespace app
{
	StateEmu::StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager)
		: ion::gamekit::State("emu", stateManager, resourceManager)
	{
		m_gui = nullptr;
		m_debuggerRegs = nullptr;
	}

	void StateEmu::OnEnterState()
	{
		//Create GUI
		//TODO
		m_gui = new ion::gui::GUI(ion::Vector2i(1024, 768));

		//Create debugger
		m_debuggerConsole = new debug::WindowConsole(*m_gui, m_masterSystem.GetConsole().GetBuffer(), ion::Vector2i(400, 400), ion::Vector2i());
		m_debuggerRegs = new debug::WindowRegs(*m_gui, m_masterSystem.GetRegisters(), ion::Vector2i(20, 20), ion::Vector2i());
		m_debuggerRAM = new debug::WindowMemory(*m_gui, m_masterSystem.GetRAM(), ion::Vector2i(800, 400), ion::Vector2i());
		m_gui->AddWindow(*m_debuggerConsole);
		m_gui->AddWindow(*m_debuggerRegs);
		m_gui->AddWindow(*m_debuggerRAM);

		//Initialise emulator
		if (!m_masterSystem.LoadROM("roms/z80.bin"))
		{
			//Error
		}
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
		//Update machine
		m_masterSystem.Update(deltaTime);

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