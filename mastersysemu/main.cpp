#include <ion/core/time/Time.h>
#include <ion/core/debug/CrashHandler.h>
#include <ion/core/platform/Platform.h>
#include "mastersysemu.h"

#include <ion/core/thread/Sleep.h>

#if ION_ONLINE_STEAM
#include <ion/online/Steam/Steam.h>
#endif

#if defined ION_PLATFORM_MACOSX
#include <unistd.h>
#include <libgen.h>
#include <mach-o/dyld.h>
#include <limits.h>
#endif

#if defined ION_PLATFORM_WINDOWS && !defined DEBUG
int  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int numargs, char** args)
#endif
{
	//Initialise platform
	ion::platform::Initialise();

	//Init crash handler/core dump
	ion::debug::InstallDefaultCrashHandler();

#if ION_ONLINE_STEAM && !_DEBUG
	//If Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
	//local Steam client and also launches this game again.
	if (SteamAPI_RestartAppIfNecessary(EVIL_EMU_APP_ID_STEAM))
	{
		return EXIT_FAILURE;
	}
#endif
    
#if defined ION_PLATFORM_MACOSX && !defined DEBUG
    char path[PATH_MAX];
    uint32_t pathLen = sizeof(path);
    int err = _NSGetExecutablePath(path, &pathLen);
    assert(!err);
    chdir(dirname(path));
#endif

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

	//Shutdown platform
	ion::platform::Shutdown();
}
