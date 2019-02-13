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
		m_debuggerState = DebuggerState::Break;
	}

	void StateEmu::OnEnterState()
	{
		//Create GUI
		//TODO
		m_gui = new ion::gui::GUI(ion::Vector2i(1024, 768));

		//Initialise emulator
		if (!m_masterSystem.LoadROM("roms/VDPTEST.sms"))
		{
			//Error
		}

		//Disassemble
		m_masterSystem.Disassemble(m_disassembly);

		//Create debugger
		m_debuggerRegsZ80 = new debug::WindowRegsZ80(*m_gui, m_masterSystem.GetRegistersZ80(), ion::Vector2i(20, 20), ion::Vector2i(200, 400));
		m_debuggerRegsVDP = new debug::WindowRegsVDP(*m_gui, m_masterSystem.GetRegistersVDP(), ion::Vector2i(230, 20), ion::Vector2i(200, 400));
		m_debuggerRAM = new debug::WindowMemory("RAM", *m_gui, m_masterSystem.GetRAM(), ion::Vector2i(440, 20), ion::Vector2i(400, 195));
		m_debuggerVRAM = new debug::WindowMemory("VRAM", *m_gui, m_masterSystem.GetVRAM(), ion::Vector2i(430, 30), ion::Vector2i(400, 195));
		m_debuggerConsole = new debug::WindowConsole(*m_gui, m_masterSystem.GetConsole().GetBuffer(), ion::Vector2i(440, 230), ion::Vector2i(400, 195));
		m_debuggerDisassembly = new debug::WindowDisassembly(*m_gui, m_disassembly, ion::Vector2i(20, 430), ion::Vector2i(850, 300));

		m_gui->AddWindow(*m_debuggerConsole);
		m_gui->AddWindow(*m_debuggerDisassembly);
		m_gui->AddWindow(*m_debuggerRegsZ80);
		m_gui->AddWindow(*m_debuggerRegsVDP);
		m_gui->AddWindow(*m_debuggerRAM);
		m_gui->AddWindow(*m_debuggerVRAM);

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
		delete m_debuggerRegsZ80;
		m_debuggerRegsZ80 = nullptr;

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
		bool debugAddressUpdated = false;

		if (m_debuggerState == DebuggerState::Run)
		{
			//Update machine
			//TODO: Instruction clock
			m_masterSystem.Update(10000);
			debugAddressUpdated = true;

			if (m_window.HasFocus())
			{
				//Break if F10
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F10))
				{
					m_debuggerState = DebuggerState::Break;
					debugAddressUpdated = true;
				}
			}
		}
		else if (m_debuggerState == DebuggerState::Break)
		{
			if (m_window.HasFocus())
			{
				//Step if F10
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F10))
				{
					m_masterSystem.Update(1);
					debugAddressUpdated = true;
				}

				//Run if F5
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F5))
				{
					m_debuggerState = DebuggerState::Run;
					debugAddressUpdated = true;
				}
			}
		}

		//Update debugger
		if (m_debuggerDisassembly && debugAddressUpdated)
		{
			m_debuggerDisassembly->HighlightAddress(m_masterSystem.GetRegistersZ80().pc);
		}

		//Update UI
		bool passGUIInput = m_window.HasFocus();
		m_gui->Update(deltaTime, passGUIInput ? keyboard : nullptr, passGUIInput ? mouse : nullptr, passGUIInput ? gamepad : nullptr);

		//Update FPS display
		m_fpsCounter.Update();
		if (m_fpsCounter.GetFrameCount() % 30 == 0)
		{
			//Set window title
			std::stringstream text;
			text.setf(std::ios::fixed, std::ios::floatfield);
			text.precision(2);
			text << "Master System Emu : FPS: " << m_fpsCounter.GetLastFPS();
			m_window.SetTitle(text.str().c_str());
		}

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