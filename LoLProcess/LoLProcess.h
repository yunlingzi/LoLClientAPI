// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.30.29
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"
#include "LoLMemory/HudManager/HudManager.h"
#include <stddef.h>

// ---------- Defines -------------

#define LoLProcess_get_remote_addr(object, field) \
	(void *) (object->thisAddr + offsetof(typeof(*object), field))

#ifndef API_EXECUTABLE
	// DLL injection : read from current process
	#define LoLProcess_get_addr(object, field) LoLProcess_get_remote_addr(object, field)
#else
	// Executable : read from target process
	#define LoLProcess_get_addr(object, field) \
		(void *) (&object->field); \
		read_from_memory ( \
			LoLClientAPI->process->proc, \
			&object->field, \
			object->thisAddr + offsetof(typeof(*object), field), \
			sizeof(object->field) \
		);
#endif

// ------ Structure declaration -------
typedef struct _LoLProcess
{
	MemProc *process;

	// Memory structures
	HudManager *hud;


}	LoLProcess;



// --------- Constructors ---------

LoLProcess *
LoLProcess_new (void);

LoLProcess *
LoLProcess_alloc (void);

// ----------- Functions ------------

bool
LoLProcess_init (LoLProcess *LoLProcess);


// --------- Destructors ----------

void
LoLProcess_free (void);


