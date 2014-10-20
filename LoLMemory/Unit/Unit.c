#include "Unit.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "Unit"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new Unit structure.
 * DWORD pUnit : The address of the Unit in the target process
 * Return		: A pointer to an allocated Unit.
 */
Unit *
Unit_new (
	DWORD pUnit
) {
	Unit *this;

	if ((this = calloc (1, sizeof(Unit))) == NULL)
		return NULL;

	if (!Unit_init (this, pUnit)) {
		Unit_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated Unit structure.
 * Unit *this : An allocated Unit to initialize.
 * DWORD pUnit : The address of the Unit in the target process
 * Return : true on success, false on failure.
 */
bool
Unit_init (
	Unit *this,
	DWORD pUnit
) {
	this->pThis = pUnit;
	return true;
}


/*
 * Description : Free an allocated Unit structure.
 * Unit *this : An allocated Unit to free.
 */
void
Unit_free (
	Unit *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a Unit is coherent
 * Unit *this : The instance to test
 * Return : true on success, false on failure
 */
bool
Unit_test (
	Unit *this
) {

	return true;
}
