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
#include <ion/audio/Engine.h>
#include <ion/audio/Buffer.h>
#include <ion/audio/Source.h>
#include <ion/audio/Voice.h>
#include <ion/audio/StreamDesc.h>

#include "debugger/WindowConsole.h"
#include "debugger/WindowDisassembly.h"
#include "debugger/WindowRegsZ80.h"
#include "debugger/WindowRegsVDP.h"
#include "debugger/WindowMemory.h"

#include "emu/MasterSystem.h"
#include "Settings.h"
#include "Constants.h"

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

		class AudioStreamDesc : public ion::audio::StreamDesc
		{
		public:
			virtual ion::audio::DataFormat GetEncodedFormat() const { return ion::audio::PCM16; }
			virtual ion::audio::DataFormat GetDecodedFormat() const { return ion::audio::PCM16; }

			virtual u32 GetNumChannels() const { return AUDIO_NUM_CHANNELS; }
			virtual u32 GetSampleRate() const { return AUDIO_SAMPLE_RATE_HZ; }
			virtual u32 GetBitsPerSample() const { return AUDIO_BUFFER_FORMAT_SIZE * 8; }
			virtual u32 GetBlockSize() const { return (GetNumChannels() * GetBitsPerSample()) / 8; }
			virtual u32 GetEncodedSizeBytes() const { return AUDIO_BUFFER_LEN_BYTES; }
			virtual u32 GetDecodedSizeBytes() const { return AUDIO_BUFFER_LEN_BYTES; }
			virtual u32 GetSizeSamples() const { return AUDIO_BUFFER_LEN_SAMPLES; }
		};

		class AudioSource : public ion::audio::Source
		{
		public:
			AudioSource();
			virtual bool OpenStream(OnStreamOpened const& onOpened);
			virtual void CloseStream(OnStreamClosed const& onClosed);
			virtual void RequestBuffer(ion::audio::SourceCallback& callback);

			void PushBuffer(const std::vector<emu::cpu::psg::SampleFormat>& buffer);

		private:
			u32 m_audioProducerBufferIdx;
			u32 m_audioConsumerBufferIdx;
			ion::audio::Buffer* m_audioBuffers[AUDIO_NUM_BUFFERS];
			AudioStreamDesc m_audioStreamDesc;
		};

		void SetupRenderer();
		void SetupAudio();
		void DumpError();

		//UI
		ion::gui::GUI* m_gui;
		ion::render::Window& m_window;
		debug::WindowConsole* m_debuggerConsole;
		debug::WindowDisassembly* m_debuggerDisassembly;
		debug::WindowRegsZ80* m_debuggerRegsZ80;
		debug::WindowRegsVDP* m_debuggerRegsVDP;
		debug::WindowMemory* m_debuggerROM;
		debug::WindowMemory* m_debuggerRAM;
		debug::WindowMemory* m_debuggerVRAM;
		ion::gamekit::FPSCounter m_fpsCounter;

		//Rendering
		ion::render::Texture* m_renderTexture;
		ion::render::Material* m_renderMaterial;
		ion::render::Quad* m_renderPrimitive;
		static const ion::render::TexCoord s_texCoords[4];

		//Audio
		ion::audio::Voice* m_audioVoice;
		AudioSource m_audioSource;

#if defined ION_RENDERER_SHADER
		ion::io::ResourceHandle<ion::render::Shader> m_shaderFlatTextured;
#endif

		//The machine
		emu::MasterSystem m_masterSystem;

		//Settings
		Settings m_settings;

		//Debugging
		DebuggerState m_debuggerState;
		std::vector<emu::cpu::z80::disassembler::Instruction> m_disassembly;
		u8 m_Z80ErrorState;
	};
}
