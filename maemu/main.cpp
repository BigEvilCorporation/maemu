#include <ion/engine/Engine.h>
#include <ion/core/time/Time.h>
#include "Maemu.h"

#include <ion/core/thread/Sleep.h>

namespace ion
{
	int EntryPoint(int numargs, char** args)
	{
		if (numargs != 2)
		{
			ion::debug::Log("maeumu :: A SEGA Master System emulator by BIG EVIL CORPORATION");
			ion::debug::Log("github.com/BigEvilCorporation/maemu\n");
			ion::debug::Log(" Usage:");
			ion::debug::Log("  maeumu.exe [rom_filename]\n");
			ion::debug::Log(" Controls:");
			ion::debug::Log("  Arrow keys, A, S");
			ion::debug::Log("  or an XInput compatible gamepad.\n");
			ion::debug::Log("<3 TRANS RIGHTS <3");
			return 0;
		}

		//Create engine
		ion::engine.Initialise("maemu", 2048, 1536, false, ion::render::Viewport::eOrtho2DAbsolute);

		app::MasterSystemEmu app;

		if (app.Initialise(args[1]))
		{
			float deltaTime = 0.0f;
			bool run = true;
			while (run)
			{
				u64 startTicks = ion::time::GetSystemTicks();

				if (run = app.Update(deltaTime))
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

		return 0;
	}
}