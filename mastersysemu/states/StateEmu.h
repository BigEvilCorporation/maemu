#pragma once

#include <ion/gamekit/StateManager.h>
#include <ion/gamekit/FPSCounter.h>
#include <ion/gui/GUI.h>
#include <ion/renderer/Window.h>
#include <ion/renderer/Camera.h>
#include <ion/renderer/Texture.h>
#include <ion/renderer/Shader.h>
#include <ion/renderer/Material.h>
#include <ion/renderer/Primitive.h>
#include <ion/renderer/TexCoord.h>

#include "debugger/WindowConsole.h"
#include "debugger/WindowDisassembly.h"
#include "debugger/WindowRegsZ80.h"
#include "debugger/WindowRegsVDP.h"
#include "debugger/WindowMemory.h"

#include "emu/MasterSystem.h"

namespace app
{
	class StateEmu : public ion::gamekit::State
	{
	public:
		StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager, ion::render::Window& window);

		virtual void OnEnterState();
		virtual void OnLeaveState();
		virtual void OnPauseState();
		virtual void OnResumeState();

		virtual bool Update(float deltaTime, ion::input::Keyboard* keyboard, ion::input::Mouse* mouse, ion::input::Gamepad* gamepad);
		virtual void Render(ion::render::Renderer& renderer, const ion::render::Camera& camera, ion::render::Viewport& viewport);

	private:
		enum class DebuggerState
		{
			Break,
			Run
		};

		void SetupRenderer();
		void DumpError();

		//UI
		ion::gui::GUI* m_gui;
		ion::render::Window& m_window;
		debug::WindowConsole* m_debuggerConsole;
		debug::WindowDisassembly* m_debuggerDisassembly;
		debug::WindowRegsZ80* m_debuggerRegsZ80;
		debug::WindowRegsVDP* m_debuggerRegsVDP;
		debug::WindowMemory* m_debuggerRAM;
		debug::WindowMemory* m_debuggerVRAM;
		ion::gamekit::FPSCounter m_fpsCounter;

		//Rendering
		ion::render::Texture* m_renderTexture;
		ion::render::Material* m_renderMaterial;
		ion::render::Quad* m_renderPrimitive;
		static const ion::render::TexCoord s_texCoords[4];

		//The machine
		emu::MasterSystem m_masterSystem;

		//Debugging
		DebuggerState m_debuggerState;
		std::vector<emu::cpu::z80::disassembler::Instruction> m_disassembly;
		u8 m_Z80ErrorState;
	};
}
