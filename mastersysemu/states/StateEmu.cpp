#include "StateEmu.h"

#include "emu/cpu/vdp/Constants.h"

namespace app
{
	static const int g_top = 128;
	static const int g_bottom = 128 + 224;
	static const int g_left = 128;
	static const int g_right = 128 + (40 * 8);
	static const float g_borderTop = (1.0f / emu::cpu::vdp::VDP_SCANLINES_PAL) * (float)g_top;
	static const float g_borderBottom = (1.0f / emu::cpu::vdp::VDP_SCANLINES_PAL) * (float)(emu::cpu::vdp::VDP_SCANLINES_PAL - g_bottom);
	static const float g_borderLeft = (1.0f / emu::cpu::vdp::VDP_SCREEN_WIDTH) * (float)g_left;
	static const float g_borderRight = (1.0f / emu::cpu::vdp::VDP_SCREEN_WIDTH) * (float)(emu::cpu::vdp::VDP_SCREEN_WIDTH - g_right);

	const ion::render::TexCoord StateEmu::s_texCoords[4] =
	{
		ion::Vector2(g_borderLeft, g_borderTop),
		ion::Vector2(g_borderLeft, 1.0f - g_borderBottom),
		ion::Vector2(1.0f - g_borderRight, 1.0f - g_borderBottom),
		ion::Vector2(1.0f - g_borderRight, g_borderTop)
	};

	StateEmu::StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager, ion::render::Window& window)
		: ion::gamekit::State("emu", stateManager, resourceManager)
		, m_window(window)
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

		//Setup rendering
		SetupRenderer();
	}

	void StateEmu::SetupRenderer()
	{
		ion::Vector2i renderBufferSize(emu::cpu::vdp::VDP_SCREEN_WIDTH, emu::cpu::vdp::VDP_SCANLINES_PAL);

		m_renderPrimitive = new ion::render::Quad(ion::render::Quad::xy, ion::Vector2(m_window.GetClientAreaWidth() / 2.0f, m_window.GetClientAreaHeight() / 2.0f));
		//m_renderPrimitive->SetTexCoords(s_texCoords);

		m_renderTexture = ion::render::Texture::Create(renderBufferSize.x, renderBufferSize.y, ion::render::Texture::Format::BGRA, ion::render::Texture::Format::BGRA, ion::render::Texture::BitsPerPixel::BPP24, false, false, NULL);

		//Setup material
		m_renderMaterial = new ion::render::Material();
		m_renderMaterial->AddDiffuseMap(m_renderTexture);
		m_renderMaterial->SetDiffuseColour(ion::Colour(1.0f, 1.0f, 1.0f));

		//Setup texture filtering
		m_renderTexture->SetMinifyFilter(ion::render::Texture::Filter::Linear);
		m_renderTexture->SetMagnifyFilter(ion::render::Texture::Filter::Linear);
		m_renderTexture->SetWrapping(ion::render::Texture::Wrapping::Clamp);
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
		//Copy framebuffer to texture
		m_renderTexture->SetPixels(ion::render::Texture::Format::BGRA, false, (u8*)m_masterSystem.GetFramebuffer().data());

		//Bind material and draw quad
		ion::Matrix4 emuMatrix;
		emuMatrix.SetTranslation(ion::Vector3(0.0f, 0.0f, 1.0f));
		m_renderMaterial->Bind(emuMatrix, camera.GetTransform().GetInverse(), renderer.GetProjectionMatrix());
		renderer.SetAlphaBlending(ion::render::Renderer::eNoBlend);
		renderer.DrawVertexBuffer(m_renderPrimitive->GetVertexBuffer(), m_renderPrimitive->GetIndexBuffer());
		m_renderMaterial->Unbind();

		//Render UI
		m_gui->Render(renderer, viewport);
	}
}