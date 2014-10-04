#include "LoLProcess.h"
#include "LoLClientAPI.h"
#include <stdlib.h>
#include <time.h>

#define _DEBUG_OBJECT_ "LoLProcess"
#include "dbg/dbg.h"

/**
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

	set_LoLClientAPI (this);

	if (!LoLProcess_init (this)) {
		dbg ("Initialization failed.");
		LoLProcess_free (this);
		return NULL;
	}

	if (!LoLProcess_test (this)) {
		dbg ("Test failed.");
		LoLProcess_free (this);
		return NULL;
	}


	return this;
}


/**
 * Description : Initialize an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to initialize.
 * Return : true on success, false on failure.
 */
bool
LoLProcess_init (
	LoLProcess *this
) {
	// Open debug file, only for DLL (use stdout for executable version)
	#ifndef API_EXECUTABLE
	if ((this->debugOutput = file_open("C:/Users/Spl3en/Desktop/C/LoLClientAPI/bin/Debug/output.txt", "a+"))) {
		dbg_set_output(this->debugOutput);
	}
	#endif

	// Get time and start logging
	struct tm now = *localtime((time_t[]) {time(NULL)});
	dbg("========================== Injection started at %d-%d-%d %d:%d:%d ==========================",
		now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

	// Detect LoL process
	if ((this->process = memproc_new ("League of Legends.exe", "League of Legends (TM) Client"))) {
		memproc_refresh_handle (this->process);

		if (memproc_detected (this->process)) {
			// Initialize memory structures
			info("Dumping process...");
			memproc_dump(this->process, this->process->base_addr + 0x1000, this->process->base_addr + 0xE05000);

			this->hud = HudManager_new (this->process);
			return true;
		}
	}

	return false;
}

/**
 * Description : Free an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to free.
 */
void
LoLProcess_free (
	LoLProcess *this
) {
	#ifdef API_EXECUTABLE
		fclose(this->debugOutput);
	#endif

	if (this != NULL)
	{
		HudManager_free (this->hud);
		free (this);
	}
}
