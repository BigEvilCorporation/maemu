#include <ion/engine/Engine.h>
#include <ion/core/time/Time.h>
#include "mastersysemu.h"

#include <ion/core/thread/Sleep.h>

int main(int numargs, char** args)
{
	//Create engine
	ion::engine.Initialise("SMS EMU", 1024, 768, false, ion::render::Viewport::eOrtho2DAbsolute);

	app::MasterSystemEmu app;

	if(app.Initialise())
	{
		float deltaTime = 0.0f;
		bool run = true;
		while(run)
		{
			u64 startTicks = ion::time::GetSystemTicks();

			if(run = app.Update(deltaTime))
			{
				app.Render();
			}

			u64 endTicks = ion::time::GetSystemTicks();
			deltaTime = (float)ion::time::TicksToSeconds(endTicks - startTicks);
		}

		app.Shutdown();
	}

	//Shutdown engine
	ion::engine.Shutdown();
}
