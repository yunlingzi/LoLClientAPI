#include "HudManager.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "HudManager"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new HudManager structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated HudManager.
 */
HudManager *
HudManager_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	HudManager *this;

	if ((this = calloc(1, sizeof(HudManager))) == NULL)
		return NULL;

	if (!HudManager_init (this, baseAddress, sizeOfModule)) {
		HudManager_free (this);
		return NULL;
	}

	return this;
}

/*
 * Description : Initialize an allocated HudManager structure.
 * HudManager *this : An allocated HudManager to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
HudManager_init (
	HudManager *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	DWORD hudManagerInstance;
	DWORD hudManagerInstanceStr = memscan_string (
		"HudManagerInstanceStr",
		baseAddress, sizeOfModule,
		"GAMESTATE_GAMELOOP HUDDraw"
	);

	if (!hudManagerInstanceStr) {
		dbg ("HudManagerInstanceStr not found.");
		return false;
	}

	// HudManagerInstanceStr has been found
	dbg ("HudManagerInstanceStr found : 0x%08X", hudManagerInstanceStr);

	unsigned char pattern [] = {
		/*	68 681C0202       push offset League_of_Legends.02021C68                           ; ASCII "GAMESTATE_GAMELOOP HUDDraw\n"
			FF35 8C55CE03     push [dword ds:League_of_Legends.3CE558C]
			83C8 01           or eax, 00000001
			50                push eax
			6A 03             push 3
			E8 2006ECFF       call League_of_Legends.0156A170
			83C4 10           add esp, 10
			8B0D 248DCE03     mov ecx, [dword ds:League_of_Legends.3CE8D24] */

		0x68, '_', '_', '_', '_',
		'?', '?', '?', '?', '?', '?',
		'?', '?', '?',
		'?',
		'?', 0x03,
		0xE8, '?', '?', '?', '?',
		'?', '?', '?',
		'?', '?', '?', '?', '?', '?'
	};

	// Replace ____ with hudManagerInstanceStr address
	int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &hudManagerInstanceStr, 4);

	// Find a reference to HudManagerAddress
	hudManagerInstance = mem_scanner ("hudManagerInstance",
		baseAddress, sizeOfModule,
		pattern,

		"xxxxx"
		"??????"
		"???"
		"?"
		"?x"
		"x????"
		"???"
		"??????",

		"xxxxx"
		"xxxxxx"
		"xxx"
		"x"
		"xx"
		"xxxxx"
		"xxx"
		"xx????"
	);

	if (hudManagerInstance)
	{
		// hudManagerInstance has been found
		this->pThis = hudManagerInstance;
		dbg ("pHudManager pointer found : 0x%08X", this->pThis);

		// Get objects from HudManager
		if (!(this->hudCamera = HudCamera_new (HudManager_get_object (this, HUD_CAMERA)))) {
			dbg ("Cannot get HudCamera.");
			return false;
		}
		dbg ("HudCamera found at 0x%08X", this->hudCamera->pThis);

		if (!(this->hudCursorTarget = HudCursorTarget_new (HudManager_get_object (this, HUD_CURSOR_TARGET)))) {
			dbg ("Cannot get hudCursorTarget.");
			return false;
		}
		dbg ("hudCursorTarget found at 0x%08X", this->hudCursorTarget->pThis);

		if (!(this->hudCameraSettings = HudCameraSettings_new (HudManager_get_object (this, HUD_CAMERA_SETTINGS)))) {
			dbg ("Cannot get hudCursorTarget.");
			return false;
		}
		dbg ("hudCameraSettings found at 0x%08X", this->hudCameraSettings->pThis);

		return true;
	}

	return false;
}

/*
 * Description : Retrieve the address of a HUD object from the HudManager
 * HudManager *this : An allocated HudManager
 * MemProc *mp : the target LoL process
 * HudObject object : the object requested
 * Return : DWORD addresss of the object requested in the target process
 */
DWORD
HudManager_get_object (
	HudManager *this,
	HudObject object
) {
	DWORD * hudObjects;

	if ((hudObjects = *((DWORD **) this->pThis)) == NULL) {
		return 0;
	}

	return hudObjects [object];
}


/*
 * Description : Free an allocated HudManager structure.
 * HudManager *this : An allocated HudManager to free.
 */
void
HudManager_free (
	HudManager *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
