#include "HudManager.h"
#include "LoLClientAPI.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "HudManager"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new HudManager structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated HudManager.
 */
HudManager *
HudManager_new (
	MemProc *mp
) {
	HudManager *this;

	if ((this = calloc(1, sizeof(HudManager))) == NULL)
		return NULL;

	if (!HudManager_init (this, mp)) {
		HudManager_free (this);
		return NULL;
	}

	return this;
}

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
) {
	MemBlock *mb = NULL;
	Buffer *pHudManagerInstance = NULL;

	BbQueue *results = memscan_search_string (
		mp, "HudManagerInstanceStr",
		"HudManager::GetInstance: Instance not created yet or already destroyed"
	);

	if (!results) {
		dbg ("HudManagerInstanceStr not found.");
		return false;
	}

	if ((mb = bb_queue_pick_first(results))) {
		// HudManagerInstanceStr has been found

		dbg ("HudManagerInstanceStr found : 0x%08X", mb->data);

		unsigned char pattern[] =
			/*  01629DE0     A1 0846BD03       mov eax, [dword ds:League_of_Legends.3BD4608] <--- pHudManagerInstance
				01629DE5     85C0              test eax, eax
				01629DE7   ▼ 75 26             jnz short League_of_Legends.01629E0F
				01629DE9     68 302FF001       push offset League_of_Legends.01F02F30 <-- HudManagerInstanceStr
				01629DEE     68 782FF001       push offset League_of_Legends.01F02F78
				01629DF3     68 74010000       push 174 <-- HudManager ID
				01629DF8     68 D82DF001       push offset League_of_Legends.01F02DD8
				01629DFD     68 C826EE01       push offset League_of_Legends.01EE26C8 */
			"?????"
			"??"
			"??"
			"\x68____"
			"\x68????"
			"\x68\x74\x01\x00\x00"
			"\x68????"
			"\x68????";

		// Replace ____ with pHudManagerInstance address
		memcpy(&pattern[10], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to HudManagerAddress
		results = memscan_search (mp, "pHudManagerInstance",
			pattern,
			"?????"
			"??"
			"??"
			"xxxxx"
			"x????"
			"xxxxx"
			"x????"
			"x????",

			"x????"
			"xx"
			"xx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
		);

		if ((pHudManagerInstance = bb_queue_pick_first(results))) {
			// pHudManagerInstance has been found
			this->pThis = read_memory_as_int (mp->proc, *((DWORD *)pHudManagerInstance->data));
			dbg ("pHudManager pointer found : 0x%08X", this->pThis);

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);

			// Get objects from HudManager
			if (!(this->hudCamera = HudCamera_new (HudManager_get_object (this, mp, HUD_CAMERA)))) {
				dbg ("Cannot get HudCamera.");
				return false;
			}

			if (!(this->hudCursorTarget = HudCursorTarget_new (HudManager_get_object (this, mp, HUD_CURSOR_TARGET)))) {
				dbg ("Cannot get hudCursorTarget.");
				return false;
			}


			return true;
		}
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
	HudManager *hudManager,
	MemProc *mp,
	HudObject object
) {
	return read_memory_as_int (mp->proc, hudManager->pThis + (object * sizeof(DWORD)));
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
