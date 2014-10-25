#include "GUIMenu.h"
#include "LoLProcess/LoLProcess.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "GUIMenu"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new GUIMenu structure.
 * MemProc *mp : The target LoL process
 * Return		: A pointer to an allocated GUIMenu.
 */
GUIMenu *
GUIMenu_new (
	MemProc *mp
) {
	GUIMenu *this;

	if ((this = calloc (1, sizeof(GUIMenu))) == NULL)
		return NULL;

	if (!GUIMenu_init (this, mp)) {
		GUIMenu_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated GUIMenu structure.
 * GUIMenu *this : An allocated GUIMenu to initialize.
 * Return : true on success, false on failure.
 */
bool
GUIMenu_init (
	GUIMenu *this,
	MemProc *mp
) {
	MemBlock *mb = NULL;
	Buffer *pGUIMenuInstance = NULL;

	BbQueue *results = memscan_search_buffer (
		mp, "GUIMenuStr",
		"GUIMenu\0", strlen("GUIMenu") + 1
	);

	if (!results || (bb_queue_get_length (results) <= 0)) {
		dbg ("GUIMenuStr not found.");
		return false;
	}

	if ((mb = bb_queue_pick_first (results))) {
		// HudManagerInstanceStr has been found
		dbg ("GUIMenuStr found : 0x%08X", mb->addr);

		unsigned char pattern[] = {
		/*		833D 5407CB03 00  cmp [dword ds:League_of_Legends.3CB0754], 0  <-- pGUIMenuInstance
				75 2A             jne short League_of_Legends.014A7F5A
				68 85D4FA01       push offset League_of_Legends.01FAD485
				68 C02BFB01       push offset League_of_Legends.01FB2BC0        ; ASCII
				68 C9040000       push 4C9
				68 7824FB01       push offset League_of_Legends.01FB2478        ; ASCII
				68 182CFB01       push offset League_of_Legends.01FB2C18        ; ASCII "GUIMenu"
				E8 620C4100       call League_of_Legends.PrintError */

			'?',  '?',  '?',  '?',  '?', '?', 0x00,
			'?',  '?',
			0x68, '?',  '?',  '?',  '?',
			0x68, '?',  '?',  '?',  '?',
			0x68, 0xC9, 0x04, 0x00, 0x00,
			0x68, '?',  '?',  '?',  '?',
			0x68, '_',  '_',  '_',  '_',
			0xE8, '?',  '?',  '?',  '?',
		};

		// Replace ____ with pHudManagerInstance address
		int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
		memcpy(&pattern[replacePos], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to GUIMenuInstance
		results = memscan_search (mp, "pGUIMenuInstance",
			pattern,
			"???????"
			"??"
			"x????"
			"x????"
			"xxxxx"
			"x????"
			"xxxxx"
			"x????",

			"xx????x"
			"xx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
		);

		if (results && (pGUIMenuInstance = bb_queue_pick_first(results))) {
			// pGUIMenuInstance has been found
			DWORD pThis = read_memory_as_int (mp->proc, *((DWORD *)pGUIMenuInstance->data));
			read_from_memory (mp->proc, this, pThis, sizeof(this));

			this->pThis = pThis;
			dbg ("pGUIMenuInstance pointer found : 0x%08X", this->pThis);

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);

			if (!(this->guiMinimap = GUIMinimap_new (
				(DWORD) LoLProcess_get_remote_addr (this, guiMinimapPtr))
			)) {
				dbg ("Cannot get guiMinimap.");
				return false;
			}

			return true;
		}
	}

	return false;
}


/*
 * Description : Free an allocated GUIMenu structure.
 * GUIMenu *this : An allocated GUIMenu to free.
 */
void
GUIMenu_free (
	GUIMenu *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a GUIMenu is coherent
 * GUIMenu *this : The instance to test
 * Return : true on success, false on failure
 */
bool
GUIMenu_test (
	GUIMenu *this
) {

	return true;
}
