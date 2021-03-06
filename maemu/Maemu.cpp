////////////////////////////////////////////////////////////////////////////////
// EvilEmu
// Game framework using ion::engine with embedded SEGA Mega Drive ROM emulator
//
// Uses mega emulation code based on the work of Lee Hammerton and Jake Turner
//
// Matt Phillips
// http://www.bigevilcorporation.co.uk
////////////////////////////////////////////////////////////////////////////////

#include "Maemu.h"

#include <ion/core/time/Time.h>
#include <ion/engine/Engine.h>

namespace app
{
	MasterSystemEmu::MasterSystemEmu()
		: ion::framework::Application("maemu")
	{
		m_camera = nullptr;
		m_stateEmu = nullptr;
	}

	bool MasterSystemEmu::Initialise(const std::string& romFilename)
	{
		//Set resource directories
		ion::engine.io.resourceManager->SetResourceDirectory<ion::render::Texture>("textures", ".ion.texture");
		ion::engine.io.resourceManager->SetResourceDirectory<ion::render::Shader>("shaders", ".ion.shader");

		if (!InitialiseRenderer())
		{
			ion::debug::Log("Failed to intialise renderer - please check your graphics device drivers");
			return false;
		}

		if (!InitialiseGameStates(romFilename))
		{
			return false;
		}

		return true;
	}

	void MasterSystemEmu::Shutdown()
	{
		ShutdownGameStates();
	}

	bool MasterSystemEmu::Update(float deltaTime)
	{
		//Update engine
		bool engineRunning = ion::engine.Update(deltaTime);

		//Update game state
		bool gameStateRunning = UpdateGameStates(deltaTime);

		return engineRunning && gameStateRunning;
	}

	void MasterSystemEmu::Render()
	{
		ion::engine.render.renderer->BeginFrame(*ion::engine.render.viewport, ion::engine.render.window->GetDeviceContext());

		ion::engine.render.renderer->ClearColour();
		ion::engine.render.renderer->ClearDepth();

		//Render current state
		m_stateManager.Render(*ion::engine.render.renderer, *m_camera, *ion::engine.render.viewport);

		ion::engine.render.renderer->SwapBuffers();
		ion::engine.render.renderer->EndFrame();
	}

	bool MasterSystemEmu::InitialiseRenderer()
	{
		m_camera = new ion::render::Camera();

		ion::engine.render.viewport->SetClearColour(ion::Colour(0.0f, 0.0f, 0.0f, 1.0f));
		ion::engine.render.camera->SetPosition(ion::Vector3(-(float)ion::engine.render.window->GetClientAreaWidth() / 2.0f, -(float)ion::engine.render.window->GetClientAreaHeight() / 2.0f, 0.1f));
		
		//Enable vsync by default
		ion::engine.render.renderer->EnableVSync(true);

		return true;
	}

	bool MasterSystemEmu::InitialiseGameStates(const std::string& romFilename)
	{
		//Create states
		m_stateEmu = new StateEmu(m_stateManager, *ion::engine.io.resourceManager, *ion::engine.render.window, romFilename);

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
		return m_stateManager.Update(deltaTime, ion::engine.input.keyboard, ion::engine.input.mouse, ion::engine.input.gamepad);
	}
}