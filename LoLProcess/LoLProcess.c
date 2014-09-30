#include "LoLProcess.h"
#include <stdlib.h>

LoLProcess *
LoLProcess_new (void)
{
	LoLProcess *this;

	if ((this = LoLProcess_alloc()) == NULL)
		return NULL;

	LoLProcess_init(this);

	return this;
}

LoLProcess *
LoLProcess_alloc (void)
{
	return calloc(1, sizeof(LoLProcess));
}

void
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
		}
	}
}

void
LoLProcess_free (LoLProcess *LoLProcess)
{
	if (LoLProcess != NULL)
	{
		free (LoLProcess);
	}
}
