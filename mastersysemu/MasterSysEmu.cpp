////////////////////////////////////////////////////////////////////////////////
// EvilEmu
// Game framework using ion::engine with embedded SEGA Mega Drive ROM emulator
//
// Uses mega emulation code based on the work of Lee Hammerton and Jake Turner
//
// Matt Phillips
// http://www.bigevilcorporation.co.uk
////////////////////////////////////////////////////////////////////////////////

#include "mastersysemu.h"

#include <ion/core/time/Time.h>

namespace app
{
	MasterSystemEmu::MasterSystemEmu() : ion::framework::Application("MasterSystemEmu")
	{
		m_renderer = nullptr;
		m_window = nullptr;
		m_viewport = nullptr;
		m_camera = nullptr;
		m_keyboard = nullptr;
		m_mouse = nullptr;
		m_gamepad = nullptr;
		m_resourceManager = nullptr;

		m_stateEmu = nullptr;
	}

	bool MasterSystemEmu::Initialise()
	{
		//Create filesystem
		m_fileSystem = new ion::io::FileSystem();

		//Create resource manager
		m_resourceManager = new ion::io::ResourceManager();
		m_resourceManager->SetResourceDirectory<ion::render::Texture>("textures", ".ion.texture");

		if (!InitialiseRenderer())
		{
			ion::debug::Log("Failed to intialise renderer - please check your graphics device drivers");
			return false;
		}

		if (!InitialiseInput())
		{
			ion::debug::Log("Failed to intialise input system - please check your device drivers");
			return false;
		}

		if (!InitialiseGameStates())
		{
			return false;
		}

		return true;
	}

	void MasterSystemEmu::Shutdown()
	{
		ShutdownGameStates();
		ShutdownInput();
		ShutdownRenderer();

		delete m_resourceManager;
		delete m_fileSystem;
	}

	bool MasterSystemEmu::Update(float deltaTime)
	{
		//Update input
		bool inputQuit = !UpdateInput(deltaTime);

		//Update window
		bool windowQuit = !m_window->Update();

		//Update game state
		bool gameStateQuit = !UpdateGameStates(deltaTime);

		return !windowQuit && !inputQuit && !gameStateQuit;
	}

	void MasterSystemEmu::Render()
	{
		m_renderer->BeginFrame(*m_viewport, m_window->GetDeviceContext());

		m_renderer->ClearColour();
		m_renderer->ClearDepth();

		//Render current state
		m_stateManager.Render(*m_renderer, *m_camera, *m_viewport);

		m_renderer->SwapBuffers();
		m_renderer->EndFrame();
	}

	bool MasterSystemEmu::InitialiseRenderer()
	{
		//Initialise windowed (will go fullscreen when settings applied)
		m_window = ion::render::Window::Create("Master System Emu", 1024, 768, false);
		m_renderer = ion::render::Renderer::Create(m_window->GetDeviceContext());
		m_viewport = new ion::render::Viewport(m_window->GetClientAreaWidth(), m_window->GetClientAreaHeight(), ion::render::Viewport::eOrtho2DAbsolute);
		m_camera = new ion::render::Camera();

		m_viewport->SetClearColour(ion::Colour(0.0f, 0.0f, 0.0f, 1.0f));
		m_camera->SetPosition(ion::Vector3(-(float)m_window->GetClientAreaWidth() / 2.0f, -(float)m_window->GetClientAreaHeight() / 2.0f, 0.1f));
		

		//Disable vsync by default
		m_renderer->EnableVSync(false);

		return true;
	}

	void MasterSystemEmu::ShutdownRenderer()
	{
		//Exit fullscreen mode
		m_window->SetFullscreen(false, 0);

		if (m_camera)
			delete m_camera;

		if (m_viewport)
			delete m_viewport;

		if (m_renderer)
			delete m_renderer;

		if (m_window)
			delete m_window;
	}

	bool MasterSystemEmu::InitialiseInput()
	{
		m_keyboard = new ion::input::Keyboard();
		m_mouse = new ion::input::Mouse();
		m_gamepad = new ion::input::Gamepad();
		return true;
	}

	void MasterSystemEmu::ShutdownInput()
	{
		if (m_gamepad)
			delete m_gamepad;

		if (m_mouse)
			delete m_mouse;

		if (m_keyboard)
			delete m_keyboard;
	}

	bool MasterSystemEmu::UpdateInput(float deltaTime)
	{
		m_keyboard->Update();
		m_mouse->Update();
		m_gamepad->Update();

		return true;
	}

	bool MasterSystemEmu::InitialiseGameStates()
	{
		//Create states
		m_stateEmu = new StateEmu(m_stateManager, *m_resourceManager, *m_window);

		//Push first state
		m_stateManager.PushState(*m_stateEmu);

		return true;
	}

	void MasterSystemEmu::ShutdownGameStates()
	{
		//delete m_stateGame;
	}

	bool MasterSystemEmu::UpdateGameStates(float deltaTime)
	{
		return m_stateManager.Update(deltaTime, m_keyboard, m_mouse, m_gamepad);
	}
}