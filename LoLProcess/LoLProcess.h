// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.30.29
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"

// Game memory structures
#include "LoLMemory/HudManager/HudManager.h"
#include "LoLMemory/HeroClient/HeroClient.h"

#include <stddef.h>

// ---------- Defines -------------

#define LoLProcess_get_remote_addr(object, field) \
	(void *) (object->pThis + offsetof(typeof(*object), field))

#ifdef API_EXECUTABLE
	// Executable : read from target process
	#define LoLProcess_get_addr(object, field) \
		(void *) (&object->field); \
		read_from_memory ( \
			LoLClientAPI->process->proc, \
			&object->field, \
			(DWORD) LoLProcess_get_remote_addr (object, field), \
			sizeof(object->field) \
		);
#else
	// DLL injection : read from current process
	#define LoLProcess_get_addr(object, field) LoLProcess_get_remote_addr(object, field)
#endif

// ------ Structure declaration -------
typedef enum {
	STATE_INITIALIZING,
	STATE_TESTING,
	STATE_READY
} LoLProcessState;

typedef struct _LoLProcess
{
	MemProc *process;

	// Memory structures
	HudManager *hudManager;
	HeroClient *heroClient;

	// Debug output
	FILE *debugOutput;

	// State
	LoLProcessState state;


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


/*
 * Description : Set the LoLprocess to a given state
 * LoLProcess *this : An allocated LoLProcess
 * Return : void
 */
void
LoLProcess_setState (
	LoLProcess *this,
	LoLProcessState state
);

/*
 * Description : Export current memory addresses to CheatEngine
 * Return : void
 */
void
LoLProcess_exportToCE (void);


// --------- Destructors ----------

/*
 * Description : Free an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to free.
 */
void
LoLProcess_free (
	LoLProcess *LoLProcess
);

