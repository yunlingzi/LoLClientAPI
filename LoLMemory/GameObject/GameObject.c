#include "GameObject.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "GameObject"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new GameObject structure.
 * Return		: A pointer to an allocated GameObject.
 */
GameObject *
GameObject_new (void)
{
	GameObject *this;

	if ((this = calloc (1, sizeof(GameObject))) == NULL)
		return NULL;

	if (!GameObject_init (this)) {
		GameObject_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated GameObject structure.
 * GameObject *this : An allocated GameObject to initialize.
 * Return : true on success, false on failure.
 */
bool
GameObject_init (
	GameObject *this
) {


	return true;
}


/*
 * Description : Free an allocated GameObject structure.
 * GameObject *this : An allocated GameObject to free.
 */
void
GameObject_free (
	GameObject *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a GameObject is coherent
 * GameObject *this : The instance to test
 * Return : true on success, false on failure
 */
bool
GameObject_test (
	GameObject *this
) {

	return true;
}
