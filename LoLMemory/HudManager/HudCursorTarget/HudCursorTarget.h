// --- Author             : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "Position/Position.h"
#include <windows.h>

// ---------- Defines -------------


// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HudCursorTarget
{
	char gap_0[12];
	Position EntityFocusedPosition;
	Position posRaw;
	Position rightClickPosition;
	char gap_30[4];
	int field_30;

	DWORD pThis;

}	HudCursorTarget;
#pragma pack(pop)

// --------- Allocators ---------

/*
 * Description 	          : Allocate a new HudCursorTarget structure.
 * DWORD pHudCursorTarget : Address of HudCursorTarget in the target process
 * Return		               : A pointer to an allocated HudCursorTarget.
 */
HudCursorTarget *
HudCursorTarget_new (
	DWORD pHudCursorTarget
);

// ----------- Functions ------------

/*
 * Description            : Initialize an allocated HudCursorTarget structure.
 * HudCursorTarget *this  : An allocated HudCursorTarget to initialize.
 * DWORD pHudCursorTarget : Address of HudCursorTarget in the target process
 * Return                 : true on success, false on failure.
 */
bool
HudCursorTarget_init (
	HudCursorTarget *this,
	DWORD pHudCursorTarget
);


/*
 * Description            : Unit tests checking if a HudCursorTarget is coherent
 * HudCursorTarget *this  : The instance to test
 * Return                 : true on success, false on failure
 */
bool
HudCursorTarget_test (
	HudCursorTarget *this
);

// --------- Destructors ----------

/*
 * Description            : Free an allocated HudCursorTarget structure.
 * HudCursorTarget *this  : An allocated HudCursorTarget to free.
 */
void
HudCursorTarget_free (
	HudCursorTarget *this
);


