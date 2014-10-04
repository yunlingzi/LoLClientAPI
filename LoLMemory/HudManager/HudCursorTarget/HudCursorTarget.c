#include "HudCursorTarget.h"
#include <stdlib.h>


/*
 * Description 	: Allocate a new HudCursorTarget structure.
 * DWORD pHudCursorTarget : Address of HudCursorTarget in the target process
 * Return		: A pointer to an allocated HudCursorTarget.
 */
HudCursorTarget *
HudCursorTarget_new (
	DWORD pHudCursorTarget
) {
	HudCursorTarget *this;

	if ((this = calloc (1, sizeof(HudCursorTarget))) == NULL)
		return NULL;

	if (!HudCursorTarget_init (this, pHudCursorTarget)) {
		HudCursorTarget_free (this);
		return NULL;
	}

	return this;
}



/*
 * Description : Initialize an allocated HudCursorTarget structure.
 * HudCursorTarget *this : An allocated HudCursorTarget to initialize.
 * DWORD pHudCursorTarget : Address of HudCursorTarget in the target process
 * Return : true on success, false on failure.
 */
bool
HudCursorTarget_init (
	HudCursorTarget *this,
	DWORD pHudCursorTarget
) {
	this->pThis = pHudCursorTarget;

	return true;
}


/*
 * Description : Free an allocated HudCursorTarget structure.
 * HudCursorTarget *this : An allocated HudCursorTarget to free.
 */
void
HudCursorTarget_free (
	HudCursorTarget *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
