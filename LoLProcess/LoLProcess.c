#include "LoLProcess.h"
#include "LoLClientAPI.h"
#include <stdlib.h>
#include <time.h>

#define __DEBUG_OBJECT__ "LoLProcess"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new LoLProcess structure.
 * Return		: A pointer to an allocated LoLProcess.
 */
LoLProcess *
LoLProcess_new (void)
{
	LoLProcess *this;

	if ((this = calloc (1, sizeof(LoLProcess))) == NULL) {
		return NULL;
	}

	if (!LoLProcess_init (this)) {
		dbg ("Initialization failed.");
		LoLProcess_free (this);
		return NULL;
	}

	// Initialization successful :
	// Bind the current LoLProcess to the LoLClientAPI instance
	set_LoLClientAPI (this);
	LoLProcess_setState (this, STATE_TESTING);

	// Unit testing
	if (!LoLProcess_test (this)) {
		dbg ("Unit tests failed.");
		LoLProcess_free (this);
		set_LoLClientAPI (NULL);
		return NULL;
	}

	LoLProcess_setState (this, STATE_READY);

	return this;
}


/*
 * Description : Set the LoLprocess to a given state
 * LoLProcess *this : An allocated LoLProcess
 * Return : void
 */
void
LoLProcess_setState (
	LoLProcess *this,
	LoLProcessState state
) {
	switch (state)
	{
		case STATE_READY:
			dbg ("API State : READY!");
		break;
		case STATE_TESTING:
			dbg ("API State : TESTING...");
		break;
		case STATE_INITIALIZING:
			dbg ("API State : INITIALIZING...");
		break;
	}

	this->state = state;
}


/*
 * Description :	Initialize an allocated LoLProcess structure.
 *					Read the game structures
 * LoLProcess *this : An allocated LoLProcess to initialize.
 * Return : true on success, false on failure.
 */
bool
LoLProcess_init (
	LoLProcess *this
) {
	// Init state
	LoLProcess_setState (this, STATE_INITIALIZING);

	// Open debug file, only for DLL (use stdout for executable version)
	#ifndef API_EXECUTABLE
	if ((this->debugOutput = file_open("C:/Users/Spl3en/Desktop/C/LoLClientAPI/bin/Debug/output.txt", "a+"))) {
		dbg_set_output(this->debugOutput);
	}
	#endif

	// Get time and start logging
	struct tm now = *localtime ((time_t[]) {time(NULL)});
	dbg("====== Injection started at %d-%d-%d %02d:%02d:%02d ======",
		now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

	// Detect LoL process
	if ((this->process = memproc_new ("League of Legends.exe", "League of Legends (TM) Client")))
	{
		memproc_refresh_handle (this->process);

		if (memproc_detected (this->process))
		{
			dbg ("LoL Process base address : 0x%08X", this->process->base_addr);

			// Get a copy of the current client memory
			info("Dumping process...");
			memproc_dump (this->process, this->process->base_addr + 0x1000, this->process->base_addr + 0xBA9000 + 0x268000);

			// Initialize the Hud Manager
			if (!(this->hudManager = HudManager_new (this->process))) {
				dbg ("Cannot get hudManager.");
				return false;
			}

			// Initialize the heroClient
			if (!(this->heroClient = HeroClient_new (this->process))) {
				dbg ("Cannot get heroClient.");
				return false;
			}

			// Initialize the championArray
			if (!(this->championArray = ChampionArray_new (this->process, this->heroClient))) {
				dbg ("Cannot get championArray.");
				return false;
			}

			// Success
			return true;
		}
	}

	return false;
}


/*
 * Description : Export current memory addresses to CheatEngine
 * LoLProcess *this : An allocated LoLProcess
 * Return : void
 */
void
LoLProcess_exportToCE (void)
{
	#ifdef DEBUG_ACTIVATED
	LoLProcess *this = get_LoLClientAPI ();

	char * cheatEngineXmlFormat = file_get_contents("LCAPIFormat.ct");
	if (!cheatEngineXmlFormat) {
		return;
	}

	char * cheatEngineOutput = malloc (strlen(cheatEngineXmlFormat) + 10000);

	sprintf (cheatEngineOutput, cheatEngineXmlFormat,
		LoLProcess_get_remote_addr(this->hudManager->hudCamera, cameraPosition),
		LoLProcess_get_remote_addr(this->hudManager->hudCamera, cameraPosition),

		LoLProcess_get_remote_addr(this->hudManager->hudCursorTarget, posRaw),
		LoLProcess_get_remote_addr(this->hudManager->hudCursorTarget, posRaw),

		LoLProcess_get_remote_addr(this->hudManager->hudCursorTarget, rightClickPosition),
		LoLProcess_get_remote_addr(this->hudManager->hudCursorTarget, rightClickPosition),

		LoLProcess_get_remote_addr(this->heroClient, team),
		LoLProcess_get_remote_addr(this->heroClient, summonerName),
		LoLProcess_get_remote_addr(this->heroClient, currentPosition),
		LoLProcess_get_remote_addr(this->heroClient, currentPosition),
		LoLProcess_get_remote_addr(this->heroClient, curHP),
		LoLProcess_get_remote_addr(this->heroClient, maxHP)
	);

	file_put_contents("LCAPI.ct", cheatEngineOutput, NULL);
	#endif
}


/*
 * Description : Free an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to free.
 */
void
LoLProcess_free (
	LoLProcess *this
) {
	if (this != NULL)
	{
		HudManager_free (this->hudManager);
		free (this);
	}
}
