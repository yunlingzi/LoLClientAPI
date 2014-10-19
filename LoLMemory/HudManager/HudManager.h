// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.37.58
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"
#include "./HudCamera/HudCamera.h"
#include "./HudCamera/HudCameraSettings.h"
#include "./HudCursorTarget/HudCursorTarget.h"

// ---------- Defines -------------
typedef enum
{
	HUD_CAMERA,
	HUD_UNK1,
	HUD_CURSOR_TARGET,
	HUD_UNK2,
	HUD_UNK3,
	HUD_CAMERA_SETTINGS

}	HudObject;

// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HudManager
{
	HudCamera * hudCamera;
	void *unk1;
	HudCursorTarget * hudCursorTarget;
	HudCameraSettings * hudCameraSettings;

	DWORD pThis;

} HudManager;
#pragma pack(pop)



// --------- Constructors ---------

/*
 * Description 	: Allocate a new HudManager structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated HudManager.
 */
HudManager *
HudManager_new (
	MemProc *mp
);


// ----------- Functions ------------

/*
 * Description : Initialize an allocated HudManager structure.
 * HudManager *this : An allocated HudManager to initialize.
 * MemProc *mp : The target LoL process
 * Return : true on success, false on failure.
 */
bool
HudManager_init (
	HudManager *this,
	MemProc *mp
);

/*
 * Description : Retrieve the address of a HUD object from the HudManager
 * HudManager *this : An allocated HudManager
 * MemProc *mp : the target LoL process
 * HudObject object : the object requested
 * Return : DWORD addresss of the object requested in the target process
 */
DWORD
HudManager_get_object (
	HudManager *hudManager,
	MemProc *mp,
	HudObject object
);

/*
 * Description : Unit tests checking if a HudManager is coherent
 * HudManager *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudManager_test (
	HudManager *this
);

// --------- Destructors ----------

void
HudManager_free (HudManager *HudManager);


