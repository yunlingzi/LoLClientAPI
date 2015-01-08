#include "HudCameraSettings.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HudCameraSettings"
#include "dbg/dbg.h"

/*
 * Description 	            : Allocate a new HudCameraSettings structure.
 * DWORD pHudCameraSettings : Address of HudCameraSettings in the target process
 * Return		                 : A pointer to an allocated HudCameraSettings.
 */
HudCameraSettings *
HudCameraSettings_new (
	DWORD pHudCameraSettings
) {
	HudCameraSettings *this;

	if ((this = calloc (1, sizeof(HudCameraSettings))) == NULL)
		return NULL;

	if (!HudCameraSettings_init (this, pHudCameraSettings)) {
		HudCameraSettings_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description              : Initialize an allocated HudCameraSettings structure.
 * HudCameraSettings *this  : An allocated HudCameraSettings to initialize.
 * DWORD pHudCameraSettings : Address of HudCameraSettings in the target process
 */
bool
HudCameraSettings_init (
	HudCameraSettings *this,
	DWORD pHudCameraSettings
) {
	if (!pHudCameraSettings) {
		dbg ("pHudCameraSettings is NULL");
		return false;
	}

	this->pThis = pHudCameraSettings;
	return true;
}


/*
 * Description              : Free an allocated HudCameraSettings structure.
 * HudCameraSettings *this  : An allocated HudCameraSettings to free.
 */
void
HudCameraSettings_free (
	HudCameraSettings *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
