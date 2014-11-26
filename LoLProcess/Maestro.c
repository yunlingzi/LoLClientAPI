#include "Maestro.h"
#include "HookEngine/HookEngine.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "Maestro"
#include "dbg/dbg.h"

// Singleton
Maestro *maestro = NULL;

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
) {
	Maestro *this;

	if ((this = calloc (1, sizeof(Maestro))) == NULL)
		return NULL;

	maestro = this;

	if (!Maestro_init (this, baseAddress, sizeOfModule)) {
		Maestro_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated Maestro structure.
 * Maestro *this : An allocated Maestro to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
Maestro_init (
	Maestro *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	this->baseAddress = baseAddress;
	this->module = GetModuleHandle ("RiotLauncher.dll");

	dbg ("Scanning the Maestro module ... (0x%08x)", baseAddress);

	// Initialize MaestroGameController
	if (!(this->maestroGameController = MaestroGameController_new (baseAddress, sizeOfModule))) {
		dbg ("Cannot get MaestroGameController.");
		return false;
	}

	return true;
}


/*
 * Description : Set hooks in Maestro module
 * Maestro *this : An allocated Maestro to initialize.
 * Return : true on success, false on failure.
 */
bool
Maestro_set_hooks (
	Maestro *this
) {
	dbg ("Functions all correctly hooked!");
	return true;
}


/*
 * Description : Remove hooks in Maestro module
 * Maestro *this : An allocated Maestro to initialize.
 * Return : true on success, false on failure.
 */
void
Maestro_unhook (
	void
) {
	dbg ("Functions correctly unhooked!");
}


/*
 * Description : Free an allocated Maestro structure.
 * Maestro *this : An allocated Maestro to free.
 */
void
Maestro_free (
	Maestro *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a Maestro is coherent
 * Maestro *this : The instance to test
 * Return : true on success, false on failure
 */
bool
Maestro_test (
	Maestro *this
) {

	return true;
}
