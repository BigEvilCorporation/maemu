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
#include <ion/renderer/Texture.h>
#include <ion/renderer/Shader.h>
#include <ion/renderer/Material.h>
#include <ion/renderer/Primitive.h>
#include <ion/renderer/Camera.h>
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
		bool InitialiseGameStates();

		void ShutdownGameStates();

		bool UpdateGameStates(float deltaTime);

		ion::render::Camera* m_camera;

		//States
		ion::gamekit::StateManager m_stateManager;
		StateEmu* m_stateEmu;

		int m_currentdisplayIdx;
	};
}