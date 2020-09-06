#include "StateEmu.h"

#include "emu/cpu/vdp/Constants.h"
#include "emu/peripherals/Joypad.h"

#include <ion/core/utils/STL.h>
#include <ion/engine/Engine.h>

namespace app
{
	const ion::render::TexCoord StateEmu::s_texCoords[4] =
	{
		ion::Vector2(0.0f, 0.0f),
		ion::Vector2(0.0f, 1.0f),
		ion::Vector2(1.0f, 1.0f),
		ion::Vector2(1.0f, 0.0f)
	};

	const ion::Vector2 StateEmu::s_fixedUISize(1024.0f, 768.0f);

	StateEmu::StateEmu(ion::gamekit::StateManager& stateManager, ion::io::ResourceManager& resourceManager, ion::render::Window& window)
		: ion::gamekit::State("emu", stateManager, resourceManager)
		, m_window(window)
	{
#if EMU_INCLUDE_DEBUGGER
		m_debuggerState = DebuggerState::Break;
		m_Z80ErrorState = 0;
#endif
		
		m_prevAudioClock = 0.0;
	}

	void StateEmu::OnEnterState()
	{
		//Create GUI
		//TODO
		m_gui = new ion::gui::GUI(ion::Vector2i(m_window.GetClientAreaWidth(), m_window.GetClientAreaHeight()), m_window.GetClientAreaHeight() / s_fixedUISize.y);

		//Initialise emulator
		if (!m_masterSystem.LoadROM("roms/sonic.sms"))
		{
			ion::debug::Error("Could not load ROM");
		}

#if EMU_INCLUDE_DEBUGGER
		//Disassemble
		m_masterSystem.Disassemble(m_disassembly);

		//Create debugger
		m_debuggerAudio = new debug::WindowAudio(*m_gui, m_audioSource, m_masterSystem.GetRegistersPSG(), ion::Vector2i(20, 20), ion::Vector2i(200, 400));
		m_debuggerRegsZ80 = new debug::WindowRegsZ80(*m_gui, m_masterSystem.GetRegistersZ80(), ion::Vector2i(20, 20), ion::Vector2i(200, 400));
		m_debuggerRegsVDP = new debug::WindowRegsVDP(*m_gui, m_masterSystem.GetRegistersVDP(), ion::Vector2i(230, 20), ion::Vector2i(200, 400));
		m_debuggerROM = new debug::WindowMemory("ROM", *m_gui, m_masterSystem.GetROM(), ion::Vector2i(450, 10), ion::Vector2i(400, 195));
		m_debuggerRAM = new debug::WindowMemory("RAM", *m_gui, m_masterSystem.GetRAM(), ion::Vector2i(440, 20), ion::Vector2i(400, 195));
		m_debuggerVRAM = new debug::WindowMemory("VRAM", *m_gui, m_masterSystem.GetVRAM(), ion::Vector2i(430, 30), ion::Vector2i(400, 195));
		m_debuggerConsole = new debug::WindowConsole(*m_gui, m_masterSystem.GetConsole().GetBuffer(), ion::Vector2i(440, 230), ion::Vector2i(400, 195));
		m_debuggerDisassembly = new debug::WindowDisassembly(*m_gui, m_disassembly, ion::Vector2i(20, 430), ion::Vector2i(850, 300));

		m_gui->AddWindow(*m_debuggerAudio);
		m_gui->AddWindow(*m_debuggerConsole);
		m_gui->AddWindow(*m_debuggerDisassembly);
		m_gui->AddWindow(*m_debuggerRegsZ80);
		m_gui->AddWindow(*m_debuggerRegsVDP);
		m_gui->AddWindow(*m_debuggerROM);
		m_gui->AddWindow(*m_debuggerRAM);
		m_gui->AddWindow(*m_debuggerVRAM);
#endif

		//Setup rendering and audio
		SetupRenderer();
		SetupAudio();

#if EMU_INCLUDE_AUDIO
		//Begin
		m_audioVoice->Play();
#endif
	}

	void StateEmu::SetupRenderer()
	{
		ion::Vector2i renderBufferSize(emu::cpu::vdp::VDP_SCREEN_WIDTH, emu::cpu::vdp::VDP_SCANLINES_NTSC);

		m_renderPrimitive = new ion::render::Quad(ion::render::Quad::xy, ion::Vector2(m_window.GetClientAreaWidth() / 2.0f, m_window.GetClientAreaHeight() / 2.0f));
		m_renderPrimitive->SetTexCoords(s_texCoords);

		m_renderTexture = ion::render::Texture::Create(renderBufferSize.x, renderBufferSize.y, ion::render::Texture::Format::BGRA, ion::render::Texture::Format::BGRA, ion::render::Texture::BitsPerPixel::BPP24, false, false, NULL);

		//Setup material
		m_renderMaterial = new ion::render::Material();
		m_renderMaterial->AddDiffuseMap(m_renderTexture);
		m_renderMaterial->SetDiffuseColour(ion::Colour(1.0f, 1.0f, 1.0f));

		//Setup texture filtering
		m_renderTexture->SetMinifyFilter(ion::render::Texture::Filter::Linear);
		m_renderTexture->SetMagnifyFilter(ion::render::Texture::Filter::Linear);
		m_renderTexture->SetWrapping(ion::render::Texture::Wrapping::Clamp);

		//Load shader
#if defined ION_RENDERER_SHADER
		m_shaderFlatTextured = m_resourceManager.GetResource<ion::render::Shader>("flattextured",
			[this](ion::render::Shader& shader)
			{
				m_gui->SetShader(&shader);
				m_renderMaterial->SetShader(&shader);
			});
#endif
	}

	void StateEmu::SetupAudio()
	{
#if EMU_INCLUDE_AUDIO
		//Create voice
		m_audioVoice = ion::engine.audio.engine->CreateVoice(m_audioSource, false);

		//Submit silent buffers
		std::vector<emu::cpu::psg::SampleFormat> silentBuffer;
		silentBuffer.resize(emu::SMS_PSG_OUTPUT_BUFFER_SIZE_SAMPLES, 0);

		for (int i = 0; i < AUDIO_NUM_INITIAL_BUFFERS; i++)
		{
			m_audioSource.PushBuffer(*m_audioVoice, silentBuffer);
		}

		//Buffer filled callback
		m_masterSystem.SetAudioCallback(
			[&](std::vector<emu::cpu::psg::SampleFormat>& buffer)
			{
				//Submit buffer
				m_audioSource.PushBuffer(*m_audioVoice, buffer);
			});
#endif
	}

	void StateEmu::OnLeaveState()
	{
#if EMU_INCLUDE_DEBUGGER
		delete m_debuggerRegsZ80;
		m_debuggerRegsZ80 = nullptr;
#endif

		delete m_gui;
		m_gui = nullptr;

#if defined ION_RENDERER_SHADER
		m_shaderFlatTextured.Clear();
#endif
	}

	void StateEmu::OnPauseState()
	{

	}

	void StateEmu::OnResumeState()
	{

	}

	bool StateEmu::Update(float deltaTime, ion::input::Keyboard* keyboard, ion::input::Mouse* mouse, ion::input::Gamepad* gamepad)
	{
		if (m_window.HasFocus())
		{
			//Update digital input
			for (int i = 0; i < emu::peripherals::Joypad::BTN_COUNT; i++)
			{
				bool state = false;

				if (keyboard)
				{
					state |= keyboard->KeyDown(m_settings.keyboardMap[i]);
				}

				if (gamepad)
				{
					state |= gamepad->ButtonDown(m_settings.gamepadMap[i]);
				}

				m_masterSystem.SetButtonState(emu::peripherals::Joypad::JOYPAD_1, (emu::peripherals::Joypad::Button)i, state);
			}

			//Update analogue input
			if (gamepad)
			{
				if (gamepad->GetLeftStick().x < 0.0f)
					m_masterSystem.SetButtonState(emu::peripherals::Joypad::JOYPAD_1, emu::peripherals::Joypad::BTN_LEFT, true);
				if (gamepad->GetLeftStick().x > 0.0f)
					m_masterSystem.SetButtonState(emu::peripherals::Joypad::JOYPAD_1, emu::peripherals::Joypad::BTN_RIGHT, true);
				if (gamepad->GetLeftStick().y > 0.0f)
					m_masterSystem.SetButtonState(emu::peripherals::Joypad::JOYPAD_1, emu::peripherals::Joypad::BTN_UP, true);
				if (gamepad->GetLeftStick().y < 0.0f)
					m_masterSystem.SetButtonState(emu::peripherals::Joypad::JOYPAD_1, emu::peripherals::Joypad::BTN_DOWN, true);
			}

			//Reset button
			if (keyboard && keyboard->KeyPressedThisFrame(ion::input::Keycode::TAB))
			{
				m_masterSystem.Reset();
			}
		}

#if EMU_INCLUDE_DEBUGGER
		bool debugAddressUpdated = false;

		if (m_debuggerState == DebuggerState::Run)
#endif
		{
#if EMU_INCLUDE_AUDIO
			//Use audio clock
			double audioClock = m_audioVoice->GetPositionSeconds();
			double stepDelta = audioClock - m_prevAudioClock;
			m_prevAudioClock = audioClock;
#else
			double stepDelta = EMU_DEFAULT_STEP_DELTA;
#endif

			//Tick machine a single frame
			u32 cycles = m_masterSystem.StepDelta(stepDelta);

#if EMU_INCLUDE_DEBUGGER
			debugAddressUpdated = true;

			if (m_window.HasFocus())
			{
				//Break if F10
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F10))
				{
#if EMU_INCLUDE_AUDIO
					m_audioVoice->Stop();
#endif
					m_debuggerState = DebuggerState::Break;
					debugAddressUpdated = true;
				}
			}
#endif
		}
#if EMU_INCLUDE_DEBUGGER
		else if (m_debuggerState == DebuggerState::Break)
		{
			if (m_window.HasFocus())
			{
				//Step if F10
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F10))
				{
					m_masterSystem.StepInstruction();
					debugAddressUpdated = true;
				}

				//Run if F5
				if (keyboard->KeyPressedThisFrame(ion::input::Keycode::F5))
				{
#if EMU_INCLUDE_AUDIO
					m_audioVoice->Play();
#endif
					m_debuggerState = DebuggerState::Run;
					debugAddressUpdated = true;
				}
			}
		}
#endif

#if EMU_INCLUDE_DEBUGGER
		//Update debugger
		if (m_debuggerDisassembly && debugAddressUpdated)
		{
			m_debuggerDisassembly->HighlightAddress(m_masterSystem.GetRegistersZ80().pc);
		}
#endif

		//Dump error if Z80 failed
		if (m_masterSystem.GetRegistersZ80().internal.err && (m_Z80ErrorState != m_masterSystem.GetRegistersZ80().internal.err))
		{
			DumpError();
			m_Z80ErrorState = m_masterSystem.GetRegistersZ80().internal.err;
		}

		//Update UI
		bool passGUIInput = m_window.HasFocus();
		m_gui->Update(deltaTime, passGUIInput ? keyboard : nullptr, passGUIInput ? mouse : nullptr, passGUIInput ? gamepad : nullptr);

		//Update FPS display
		m_fpsCounter.Update();

		//Set window title
		std::stringstream text;
		text.setf(std::ios::fixed, std::ios::floatfield);
		text.precision(2);
		text << "maemu : FPS: " << m_fpsCounter.GetLastFPS()
			<< " :: audio clock: " << m_audioVoice->GetPositionSeconds()
			<< " :: sample clock: " << ((float)m_masterSystem.GetAudioSamplesWritten() / emu::SMS_PSG_OUTPUT_SAMPLE_RATE)
			<< " :: Z80 clock: " << ((float)m_masterSystem.GetZ80CyclesExecuted() / emu::SMS_Z80_CYCLES_PER_SECOND_NTSC)
			<< " :: buffers queued: " << m_audioVoice->GetQueuedBuffers();
		m_window.SetTitle(text.str().c_str());

		return true;
	}

	void StateEmu::Render(ion::render::Renderer& renderer, const ion::render::Camera& camera, ion::render::Viewport& viewport)
	{
		//Copy framebuffer to texture
		m_renderTexture->SetPixels(ion::render::Texture::Format::BGRA, false, (u8*)m_masterSystem.GetFramebuffer().data());

		//Bind material and draw quad
		ion::Matrix4 emuMatrix;
		emuMatrix.SetTranslation(ion::Vector3(m_window.GetClientAreaWidth() / 2.0f, m_window.GetClientAreaHeight() / 2.0f, 1.0f));
		m_renderMaterial->Bind(emuMatrix, camera.GetTransform().GetInverse(), renderer.GetProjectionMatrix());
		renderer.SetAlphaBlending(ion::render::Renderer::eNoBlend);
		renderer.DrawVertexBuffer(m_renderPrimitive->GetVertexBuffer(), m_renderPrimitive->GetIndexBuffer());
		m_renderMaterial->Unbind();

		//Render UI
		m_gui->Render(renderer, viewport);
	}

	void StateEmu::DumpError()
	{
		std::stringstream error;
		error << "Error: Z80 halted" << std::endl << "PC history: " << std::endl;

		std::vector<emu::cpu::z80::Registers> history;
		m_masterSystem.GetPCHistory(history);

		for (int i = 0; i < history.size(); i++)
		{
			std::vector<emu::cpu::z80::disassembler::Instruction> instructions;
			m_masterSystem.Disassemble(instructions, history[i].pc, 1);

			error << i << " : 0x" << SSTREAM_HEX4(history[i].pc);
			error << " AF:" << SSTREAM_HEX4(history[i].main.af);
			error << " BC:" << SSTREAM_HEX4(history[i].main.bc);
			error << " DE:" << SSTREAM_HEX4(history[i].main.de);
			error << " HL:" << SSTREAM_HEX4(history[i].main.hl);
			error << " AF':" << SSTREAM_HEX4(history[i].alt.af);
			error << " BC':" << SSTREAM_HEX4(history[i].alt.bc);
			error << " DE':" << SSTREAM_HEX4(history[i].alt.de);
			error << " HL:" << SSTREAM_HEX4(history[i].main.hl);
			error << " IX:" << SSTREAM_HEX4(history[i].ix);
			error << " IY:" << SSTREAM_HEX4(history[i].iy);
			error << " SP:" << SSTREAM_HEX4(history[i].sp);
			error << std::endl;

			if (instructions.size() > 0)
			{
				error << emu::cpu::z80::disassembler::ToText(instructions[0]);
			}
			else
			{
				error << "?";
			}

			error << std::endl;
		}

		ion::debug::Log(error.str().c_str());
	}
}