#include "LoLProcess/LoLProcess.h"
#include "LoLClientAPI/LoLClientAPI.h"

#define __DEBUG_OBJECT__ "LoLServerAPI::EntryPoint"
#include "dbg/dbg.h"


// Connection with the server
LoLClientAPI * connection = NULL;

/*
 * Description :	Function called when the DLL in loaded or the executable is launched
 * 					Initiate a connection with the server API
 */
void startClient (void)
{
	connection = LoLClientAPI_new ();

	float x, y;
	get_camera_position (&x, &y);
	printf("Camera position = %f / %f\n", x, y);
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
