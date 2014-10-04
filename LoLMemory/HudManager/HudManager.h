// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.37.58
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"
#include "./HudCamera/HudCamera.h"
#include "./HudCursorTarget/HudCursorTarget.h"

// ---------- Defines -------------
typedef enum
{
	HUD_CAMERA,
	HUD_UNK1,
	HUD_CURSOR_TARGET,

}	HudObject;

// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HudManager
{
	HudCamera * hudCamera;
	void *unk1;
	HudCursorTarget * hudCursorTarget;

	DWORD pThis;

} HudManager;
#pragma pack(pop)



// --------- Constructors ---------

HudManager *
HudManager_new (MemProc *mp);

HudManager *
HudManager_alloc (void);

// ----------- Functions ------------

bool
HudManager_init (HudManager *HudManager, MemProc *mp);

bool
HudManager_test (HudManager *hud);

DWORD
HudManager_get_object (HudManager *hudManager, MemProc *mp, HudObject object);

// --------- Destructors ----------

void
HudManager_free (HudManager *HudManager);


