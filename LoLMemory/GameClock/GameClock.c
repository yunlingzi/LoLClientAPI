#include "GameClock.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "GameClock"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new GameClock structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated GameClock.
 */
GameClock *
GameClock_new (
	MemProc *mp
) {
	GameClock *this;

	if ((this = calloc(1, sizeof(GameClock))) == NULL)
		return NULL;

	if (!GameClock_init (this, mp)) {
		GameClock_free (this);
		return NULL;
	}

	return this;
}

/*
 * Description : Initialize an allocated GameClock structure.
 * GameClock *this : An allocated GameClock to initialize.
 * MemProc *mp : The target LoL process
 * Return : true on success, false on failure.
 */
bool
GameClock_init (
	GameClock *this,
	MemProc *mp
) {
	MemBlock *mb = NULL;
	Buffer *pGameClockInstance = NULL;

	BbQueue *results = memscan_search_string (
		mp, "GameClockInstanceStr",
		"sGameClockInstance && sGameClockInstance->IsInitialized()"
	);

	if (!results) {
		dbg ("GameClockInstanceStr not found.");
		return false;
	}

	if ((mb = bb_queue_pick_first(results))) {
		// GameClockInstanceStr has been found

		dbg ("GameClockInstanceStr found : 0x%08X", mb->addr);

		unsigned char pattern[] = {
		/*	8B0D E46A5503   mov ecx, [dword ds:League_of_Legends.GameClockInstance]
			85C9            test ecx, ecx
			74 0B           je short League_of_Legends.00D468CF
			8B01            mov eax, [dword ds:ecx]
			8B40 20         mov eax, [dword ds:eax+20]
			FFD0            call eax 									  ; gameClockInstance->isInitialized()
			84C0            test al, al
			75 26           jne short League_of_Legends.00D468F5
			68 A8BE8B01     push offset League_of_Legends.018BBEA8        ; ASCII "Riot::`anonymous-namespace'::ValidateGameClockInstance"
			6A 2E           push 2E
			68 00BE8B01     push offset League_of_Legends.018BBE00        ; ASCII
			33D2            xor edx, edx
			B9 6CBE8B01     mov ecx, offset League_of_Legends.018BBE6C    ; ASCII "sGameClockInstance && sGameClockInstance->IsInitialized()"
			E8 09524100     call League_of_Legends.0115BAF0 */

			0x8B, '?', '?', '?', '?', '?',
			0x85, '?',
			0x74, '?',
			'?',  '?',
			'?',  '?', '?',
			0xFF, '?',
			0x84, '?',
			0x75, '?',
			0x68, '?', '?', '?', '?',
			0x6A, '?',
			0x68, '?', '?', '?', '?',
			0x33, '?',
			0xB9, '_', '_', '_', '_'
		};

		// Replace ____ with pGameClockInstance address
		int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
		memcpy(&pattern[replacePos], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to GameClockAddress
		results = memscan_search (mp, "pGameClockInstance",
			pattern,
			"x?????"
			"x?"
			"x?"
			"??"
			"???"
			"x?"
			"x?"
			"x?"
			"x????"
			"x?"
			"x????"
			"x?"
			"xxxxx",

			"xx????"
			"xx"
			"xx"
			"xx"
			"xxx"
			"xx"
			"xx"
			"xx"
			"xxxxx"
			"xx"
			"xxxxx"
			"xx"
			"xxxxx"
		);

		if (results && (pGameClockInstance = bb_queue_pick_first(results))) {
			// pGameClockInstance has been found
			this->pThis = read_memory_as_int (mp->proc, *((DWORD *)pGameClockInstance->data));
			dbg ("pGameClock pointer found : 0x%08X", this->pThis);

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);

			return true;
		}
	}

	return false;
}


/*
 * Description : Free an allocated GameClock structure.
 * GameClock *this : An allocated GameClock to free.
 */
void
GameClock_free (
	GameClock *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
