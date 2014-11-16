#include "LoLProcess/LoLProcess.h"
#include "LoLClientAPI/LoLClientAPI.h"
#include "LoLClientAPI/LoLClientInterface.h"

#define __DEBUG_OBJECT__ "EntryPoint"
#include "dbg/dbg.h"


// Connection with the server
LoLClientAPI * connection = NULL;

/*
 * Description :	Function called when the DLL in loaded or the executable is launched
 * 					Initiate a connection with the server API
 */
void startClient (void)
{
	while (connection == NULL) {
		connection = LoLClientAPI_new ();
		if (connection == NULL) {
			dbg ("LoLServerAPI is not ready yet ? Retrying to connect to LoLServerAPI in 3 seconds...");
			Sleep (3000);
		}
	}

	dbg ("LoLServerAPI found ! Continue...");

	set_api_ready (connection);
}


/*
 * Description :	Function called when the DLL in ejected.
 * 					Basically, it cleans the dll from the memory and close the connection with the server
 */
void endClient (void)
{
	LoLClientAPI_free (connection);
}


/*
 * Description :	DLL entry point.
 */
bool WINAPI DllMain (HMODULE dll, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) startClient, NULL, 0, NULL);
		break;

		case DLL_PROCESS_DETACH:
			endClient ();
		break;
	}

	return true;
}


/*
 * Description :	Executable entry point.
 */
int main (int argc, char **argv)
{
	startClient ();

	endClient ();

	return 0;
}
