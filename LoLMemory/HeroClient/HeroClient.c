#include "HeroClient.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HeroClient"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new HeroClient structure.
 * MemProc *mp : The target LoL process
 * Return		: A pointer to an allocated HeroClient.
 */
HeroClient *
HeroClient_new (
	MemProc *mp
) {
	HeroClient *this;

	if ((this = calloc (1, sizeof(HeroClient))) == NULL)
		return NULL;

	if (!HeroClient_init (this, mp)) {
		HeroClient_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to initialize.
 * MemProc *mp : The target LoL process
 * Return : true on success, false on failure.
 */
bool
HeroClient_init (
	HeroClient *this,
	MemProc *mp
) {
	MemBlock *mb = NULL;
	Buffer *heroClientInstance = NULL;

	BbQueue *results = memscan_search_string (
		mp, "HeroClientStr",
		"!Player || Player != this"
	);

	if (!results) {
		dbg ("HeroClientStr not found.");
		return false;
	}

	if ((mb = bb_queue_pick_first (results))) {
		// HeroClientStr has been found
		dbg ("HeroClientStr found : 0x%08X", mb->addr);

		unsigned char pattern[] =
			/*	     A1 8808A603       mov eax, [dword ds:League_of_Legends.3A60888] <-- HeroClientInstance
				     85C0              test eax, eax
				   ▼ 74 25             je short League_of_Legends.0131272A
				     3BC7              cmp eax, edi
				   ▼ 75 21             jne short League_of_Legends.0131272A
				     68 65D4D501       push offset League_of_Legends.01D5D465
				     68 103CD701       push offset League_of_Legends.01D73C10
				     68 72050000       push 572
				     68 403AD701       push offset League_of_Legends.01D73A40
				     68 303CD701       push offset League_of_Legends.01D73C30             ; ASCII "!Player || Player != this"
				     E8 29653500       call League_of_Legends.01668C50
			*/
			"?????"
			"??"
			"??"
			"??"
			"??"
			"\x68????"
			"\x68????"
			"\x68\x72\x05\x00\x00"
			"\x68????"
			"\x68____"
			"\xE8????";

		// Replace ____ with HeroClientStr address
		int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
		memcpy(&pattern[replacePos], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to HudManagerAddress
		results = memscan_search (mp, "HeroClientInstance",
			pattern,
			"?????"
			"??"
			"??"
			"??"
			"??"
			"x????"
			"x????"
			"xxxxx"
			"x????"
			"xxxxx"
			"x????",

			"x????"
			"xx"
			"xx"
			"xx"
			"xx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
		);

		if (results && (heroClientInstance = bb_queue_pick_first(results))) {
			// heroClientInstance has been found
			memcpy(&this->thisStaticPtr, heroClientInstance->data, sizeof(DWORD));
			this->pThis = read_memory_as_int (mp->proc, *((DWORD *) heroClientInstance->data));
			dbg ("pHeroClient found : 0x%08X", this->pThis);

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);

			return true;
		}
	}


	return true;
}


/*
 * Description : Free an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to free.
 */
void
HeroClient_free (
	HeroClient *this
) {
	if (this != NULL)
	{
		free (this);
	}
}

