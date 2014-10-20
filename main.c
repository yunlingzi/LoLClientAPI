#include "LoLClientAPI.h"
#include "LoLProcess/LoLProcess.h"


/*
 * Description :	Function called when the DLL in injected or the executable is launched
 * 					It injects LCAPI into LoL process, find game structures and store them
 *					into a custom structure
 */
void startInjection (void)
{
	// Install LoLClientAPI inside League of Legends.exe process
	if (!LoLProcess_new ()) {
		warning ("Injection failed.");
		return;
	}

	// Create cheatengine file
	#ifdef DEBUG_ACTIVATED
		LoLProcess_exportToCE ();
	#endif
}


/*
 * Description :	Function called when the DLL in ejected.
 * 					Basically, it cleans the dll and the memory allocated from the LoL process
 */
void endInjection (void)
{
	LoLProcess_free (get_LoLClientAPI());
}


/*
 * Description :	DLL entry point.
 */
bool WINAPI DllMain (HMODULE dll, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) startInjection, NULL, 0, NULL);
		break;

		case DLL_PROCESS_DETACH:
			endInjection ();
		break;
	}

	return true;
}


/*
 * Description :	Executable entry point.
 */
int main (int argc, char **argv)
{
	startInjection ();

	endInjection ();

	return 0;
}
