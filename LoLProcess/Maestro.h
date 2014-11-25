// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "LoLMemory/MaestroGameController/MaestroGameController.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _Maestro
{
    HMODULE module;
    DWORD baseAddress;

	// Maestro structures
	MaestroGameController *maestroGameController;

	// Original hooked functions

}	Maestro;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new Maestro structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated Maestro.
 */
Maestro *
Maestro_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);

// ----------- Functions ------------

/*
 * Description : Set hooks in Maestro module
 * Maestro *this : An allocated Maestro to initialize.
 * Return : true on success, false on failure.
 */
bool
Maestro_set_hooks (
	Maestro *this
);

/*
 * Description : Remove hooks in Maestro module
 * Maestro *this : An allocated Maestro to initialize.
 * Return : true on success, false on failure.
 */
void
Maestro_remove_hooks (
	void
);


/*
 * Description : Initialize an allocated Maestro structure.
 * Maestro *this : An allocated Maestro to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
Maestro_init (
	Maestro *this,
	DWORD baseAddress,
	DWORD sizeOfModule
);

/*
 * Description : Unit tests checking if a Maestro is coherent
 * Maestro *this : The instance to test
 * Return : true on success, false on failure
 */
bool
Maestro_test (
	Maestro *this
);


// --------- Hooked functions -----

// --------- Destructors ----------

/*
 * Description : Free an allocated Maestro structure.
 * Maestro *this : An allocated Maestro to free.
 */
void
Maestro_free (
	Maestro *this
);


