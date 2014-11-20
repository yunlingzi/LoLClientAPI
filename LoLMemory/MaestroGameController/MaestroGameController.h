// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "MemProc/MemProc.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _MaestroGameController
{


	DWORD pThis;

}	MaestroGameController;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new MaestroGameController structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated MaestroGameController.
 */
MaestroGameController *
MaestroGameController_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated MaestroGameController structure.
 * MaestroGameController *this : An allocated MaestroGameController to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
MaestroGameController_init (
	MaestroGameController *this,
	DWORD baseAddress,
	DWORD sizeOfModule
);

/*
 * Description : Unit tests checking if a MaestroGameController is coherent
 * MaestroGameController *this : The instance to test
 * Return : true on success, false on failure
 */
bool
MaestroGameController_test (
	MaestroGameController *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated MaestroGameController structure.
 * MaestroGameController *this : An allocated MaestroGameController to free.
 */
void
MaestroGameController_free (
	MaestroGameController *this
);


