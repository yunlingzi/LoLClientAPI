#include "HudCamera.h"
#include <stdlib.h>


/**
 * Description 	: Allocate a new HudCamera structure.
 * DWORD pHudCamera : Address of HudCamera in the target process
 * Return		: A pointer to an allocated HudCamera.
 */
HudCamera *
HudCamera_new (
	DWORD pHudCamera
) {
	HudCamera *this;

	if ((this = calloc (1, sizeof(HudCamera))) == NULL)
		return NULL;

	if (!HudCamera_init (this, pHudCamera)) {
		HudCamera_free (this);
		return NULL;
	}

	return this;
}


/**
 * Description : Initialize an allocated HudCamera structure.
 * HudCamera *this : An allocated HudCamera to initialize.
 * DWORD pHudCamera : Address of HudCamera in the target process
 * Return : true on success, false on failure.
 */
bool
HudCamera_init (
	HudCamera *this,
	DWORD pHudCamera
) {
	this->pThis = pHudCamera;

	return true;
}


/**
 * Description : Free an allocated HudCamera structure.
 * HudCamera *this : An allocated HudCamera to free.
 */
void
HudCamera_free (
	HudCamera *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
