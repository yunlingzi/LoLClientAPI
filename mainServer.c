#include "LoLProcess/LoLProcess.h"
#include "LoLServerAPI/LoLServerAPI.h"

#define __DEBUG_OBJECT__ "EntryPoint"
#include "dbg/dbg.h"

// Connection with the client
LoLServerAPI * connection = NULL;

/*
 * Description :	Function called when the DLL in injected or the executable is launched
 * 					It injects LCAPI into LoL process, find game structures and store them
 *					into a custom structure
 */
void startInjection (void)
{
	// Install LoLServerAPI inside League of Legends.exe process
	if (!LoLProcess_new ()) {
		warn ("Injection failed.");
		return;
	}

	// Create CheatEngine file
	LoLProcess_exportToCE ();

	// Instanciate and listen for a connection
	if ((connection = LoLServerAPI_new ()) == NULL) {
		warn ("API server connection error.");
		return;
	}

	// Answer requests
	LoLServerAPI_main (connection);

	// Confirm connection closed
	connection->closed = true;
}


/*
 * Description :	Function called when the DLL in ejected.
 * 					Basically, it cleans the dll and the memory allocated from the LoL process
 */
void endInjection (void)
{
	LoLServerAPI_free (connection);
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
