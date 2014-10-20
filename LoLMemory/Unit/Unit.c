#include "Unit.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "Unit"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new Unit structure.
 * Return		: A pointer to an allocated Unit.
 */
Unit *
Unit_new (void)
{
	Unit *this;

	if ((this = calloc (1, sizeof(Unit))) == NULL)
		return NULL;

	if (!Unit_init (this)) {
		Unit_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated Unit structure.
 * Unit *this : An allocated Unit to initialize.
 * Return : true on success, false on failure.
 */
bool
Unit_init (
	Unit *this
) {

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
