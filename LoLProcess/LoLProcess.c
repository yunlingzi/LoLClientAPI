#include "LoLProcess.h"
#include <stdlib.h>
#include <time.h>

#define _DEBUG_OBJECT__ "LoLProcess"

// Client process handle
extern LoLProcess *LoLClientAPI;
FILE * debugOutput = NULL;

LoLProcess *
LoLProcess_new (void)
{
	LoLProcess *this;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	// Open debug file, only for DLL (use stdout for executable)
	#ifndef API_EXECUTABLE
	if ((debugOutput = file_open("C:/Users/Spl3en/Desktop/C/LoLClientAPI/bin/Debug/output.txt", "a+"))) {
		dbg_set_output(debugOutput);
	}
	#endif

	dbg("========================== Injection started at %d-%d-%d %d:%d:%d ==========================",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	if ((this = LoLProcess_alloc()) == NULL)
		return NULL;

	if (!LoLProcess_init(this)) {
		LoLProcess_free ();
		return NULL;
	}

	LoLClientAPI = this;

	return this;
}

LoLProcess *
LoLProcess_alloc (void)
{
	return calloc(1, sizeof(LoLProcess));
}

bool
LoLProcess_init (LoLProcess *this)
{
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

void
LoLProcess_free ()
{
	#ifdef API_EXECUTABLE
		fclose(debugOutput);
	#endif

	if (LoLClientAPI != NULL)
	{
		HudManager_free (LoLClientAPI->hud);
		free (LoLClientAPI);
	}
}
