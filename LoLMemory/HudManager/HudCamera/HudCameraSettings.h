// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"

// ---------- Defines -------------


// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HudCameraSettings
{
	char field_0[188];
	int cameraActivated;

	DWORD pThis;

}	HudCameraSettings;
#pragma pack(pop)



// --------- Allocators ---------

/*
 * Description 	: Allocate a new HudCameraSettings structure.
 * DWORD pHudCameraSettings : Address of HudCameraSettings in the target process
 * Return		: A pointer to an allocated HudCameraSettings.
 */
HudCameraSettings *
HudCameraSettings_new (
	DWORD pHudCameraSettings
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated HudCameraSettings structure.
 * HudCameraSettings *this : An allocated HudCameraSettings to initialize.
 * DWORD pHudCameraSettings : Address of HudCameraSettings in the target process
 */
bool
HudCameraSettings_init (
	HudCameraSettings *this,
	DWORD pHudCameraSettings
);


/*
 * Description : Unit tests checking if a HudCameraSettings is coherent
 * HudCameraSettings *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudCameraSettings_test (
	HudCameraSettings *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated HudCameraSettings structure.
 * HudCameraSettings *this : An allocated HudCameraSettings to free.
 */
void
HudCameraSettings_free (
	HudCameraSettings *this
);


