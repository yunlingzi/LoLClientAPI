// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.30.29
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"

// Game memory structures
#include "LoLProcess/Maestro.h"
#include "LoLProcess/LoLModule.h"
#include "HookEngine/HookEngine.h"

// ---------- Defines -------------
// DLL injection : read from current process
#define LoLProcess_get_addr(object, field) \
	(void *) (object->pThis + offsetof(typeof(*object), field))


// ------ Structure declaration -------
typedef enum {
	STATE_INITIALIZING,
	STATE_TESTING,
	STATE_READY
} LoLProcessState;

typedef struct _LoLProcess
{
	Maestro *maestro;
	LoLModule *lol;

	// Window handle
	HWND hwnd;

	// State
	LoLProcessState state;

	// Hook engine handle
	HookEngine *hookEngine;

	// File handle to debug output
	FILE *debugOutput;

	// Path to the application
	char * appPath;

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
 * LoLProcessState state : Set the state of the LoLProcess
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

/*
 * Description : Load the Hook Engine into the LoL process
 * LoLProcess *this : An allocated LoLProcess
 * Return : void
 */
bool
LoLProcess_load_hook_engine (
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

