#include "Maestro.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "Maestro"
#include "dbg/dbg.h"

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
