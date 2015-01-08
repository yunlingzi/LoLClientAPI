#include "MaestroMessageAgent.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "MaestroMessageAgent"
#include "dbg/dbg.h"

/*
 * Description 	             : Allocate a new MaestroMessageAgent structure.
 * Return		                  : A pointer to an allocated MaestroMessageAgent.
 */
MaestroMessageAgent *
MaestroMessageAgent_new (void)
{
	MaestroMessageAgent *this;

	if ((this = calloc (1, sizeof(MaestroMessageAgent))) == NULL)
		return NULL;

	if (!MaestroMessageAgent_init (this)) {
		MaestroMessageAgent_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description               : Initialize an allocated MaestroMessageAgent structure.
 * MaestroMessageAgent *this : An allocated MaestroMessageAgent to initialize.
 * Return                    : true on success, false on failure.
 */
bool
MaestroMessageAgent_init (
	MaestroMessageAgent *this
) {

	return true;
}


/*
 * Description               : Free an allocated MaestroMessageAgent structure.
 * MaestroMessageAgent *this : An allocated MaestroMessageAgent to free.
 */
void
MaestroMessageAgent_free (
	MaestroMessageAgent *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description               : Unit tests checking if a MaestroMessageAgent is coherent
 * MaestroMessageAgent *this : The instance to test
 * Return                    : true on success, false on failure
 */
bool
MaestroMessageAgent_test (
	MaestroMessageAgent *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	return true;
}
