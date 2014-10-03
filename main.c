#include "LoLClientAPI.h"
#include "Utils/Utils.h"
#include "Ztring/Ztring.h"
#include "LoLProcess/LoLProcess.h"
#include <windows.h>

int WINAPI startInjection (void)
{
	// Install LoLClientAPI inside League of Legends.exe process
	LoLProcess_new ();

	float x, y;
	get_camera_position(&x, &y);
	set_camera_position(x + 1000.0, x + 1000.0);

	return 0;
}

int WINAPI endInjection (void)
{
	LoLProcess_free ();
	return 0;
}


// DLL entry point
bool WINAPI DllMain (HMODULE dll, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) startInjection, NULL, 0, NULL);
		break;

		case DLL_PROCESS_DETACH:
			endInjection ();
		break;
	}

	return true;
}

// Executable entry point
int main (int argc, char **argv)
{
	startInjection ();
}
