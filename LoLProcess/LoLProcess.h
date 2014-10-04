// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.30.29
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"

// Game memory structures
#include "LoLMemory/HudManager/HudManager.h"

#include <stddef.h>

// ---------- Defines -------------

#define LoLProcess_get_remote_addr(object, field) \
	(void *) (object->pThis + offsetof(typeof(*object), field))

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
			object->pThis + offsetof(typeof(*object), field), \
			sizeof(object->field) \
		);
#endif

// ------ Structure declaration -------
typedef struct _LoLProcess
{
	MemProc *process;

	// Memory structures
	HudManager *hudManager;


	// Debug output
	FILE *debugOutput;


}	LoLProcess;


// --------- Allocators ---------

/*
 * Description 	: Allocate a new LoLProcess structure.
 * Return		: A pointer to an allocated LoLProcess.
 */
LoLProcess *
LoLProcess_new (void);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to initialize.
 */
bool
LoLProcess_init (
	LoLProcess *this
);

/*
 * Description : Unit tests checking if the LoLProcess is correct
 * Return : true on success, false on failure
 */
bool
LoLProcess_test (
	LoLProcess *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to free.
 */
void
LoLProcess_free (
	LoLProcess *LoLProcess
);

