#include "LoLProcess/LoLProcess.h"
#include "LoLServerAPI/LoLServerAPI.h"

#define __DEBUG_OBJECT__ "EntryPoint"
#include "dbg/dbg.h"

// Connection with the client
LoLServerAPI * connection = NULL;


/*
 * Description :	Function called when the DLL in injected in League of Legends.exe process.
 * 					It installs LCAPI into LoL process, find game structures and store them
 *					into a LoLProcess structure.
 */
void startInjection (void)
{
	LoLProcess *LoL;
	srand (time(NULL));

	// Install LoLServerAPI inside League of Legends.exe process
	if ((LoL = LoLProcess_new ()) == NULL) {
		warn ("Injection failed.");
		return;
	}

	// Create CheatEngine file (optional)
	LoLProcess_exportToCE (LoL);

	// Instanciate and listen to a connection
	if ((connection = LoLServerAPI_new ()) == NULL) {
		warn ("API server connection error.");
		return;
	}

	// Answer to requests
	LoLServerAPI_main (connection);

	// Clean and exit
	dbg ("ServerAPI cleaning memory...");
	LoLProcess_free (LoL);
	LoLServerAPI_free (connection);
	dbg ("ServerAPI stopped working normally.");
}

/*
 * Description :	Function called when the DLL in ejected.
 */
void endInjection (void)
{
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
