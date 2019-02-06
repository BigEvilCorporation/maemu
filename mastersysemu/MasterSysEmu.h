////////////////////////////////////////////////////////////////////////////////
// MasterSystemEmu
// An experiment
//
// Matt Phillips
// http://www.bigevilcorporation.co.uk
////////////////////////////////////////////////////////////////////////////////

#include <ion/core/bootstrap/Application.h>
#include <ion/core/debug/Debug.h>
#include <ion/core/containers/FixedArray.h>
#include <ion/renderer/Renderer.h>
#include <ion/renderer/Window.h>
#include <ion/renderer/Viewport.h>
#include <ion/renderer/Texture.h>
#include <ion/renderer/Shader.h>
#include <ion/renderer/Material.h>
#include <ion/renderer/Primitive.h>
#include <ion/renderer/Camera.h>
#include <ion/input/Keyboard.h>
#include <ion/input/Mouse.h>
#include <ion/input/Gamepad.h>
#include <ion/io/FileSystem.h>
#include <ion/io/ResourceManager.h>
#include <ion/gamekit/StateManager.h>

#include "states/StateEmu.h"

namespace app
{
	class MasterSystemEmu : public ion::framework::Application
	{
	public:
		MasterSystemEmu();

		virtual bool Initialise();
		virtual void Shutdown();
		virtual bool Update(float deltaTime);
		virtual void Render();

	private:

		bool InitialiseRenderer();
		bool InitialiseInput();
		bool InitialiseGameStates();

		void ShutdownRenderer();
		void ShutdownInput();
		void ShutdownGameStates();

		bool UpdateInput(float deltaTime);
		bool UpdateGameStates(float deltaTime);

		ion::render::Renderer* m_renderer;
		ion::render::Window* m_window;
		ion::render::Viewport* m_viewport;
		ion::render::Camera* m_camera;
		ion::input::Keyboard* m_keyboard;
		ion::input::Mouse* m_mouse;
		ion::input::Gamepad* m_gamepad;

		ion::io::ResourceManager* m_resourceManager;
		ion::io::FileSystem* m_fileSystem;

		//States
		ion::gamekit::StateManager m_stateManager;
		StateEmu* m_stateEmu;

		int m_currentdisplayIdx;
	};
}