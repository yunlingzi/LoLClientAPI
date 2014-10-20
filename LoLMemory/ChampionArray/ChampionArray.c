#include "ChampionArray.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "ChampionArray"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new ChampionArray structure.
 * MemProc *mp : The target LoL process
 * HeroClient *heroClient : The HeroClient instance
 * Return		: A pointer to an allocated ChampionArray.
 */
ChampionArray *
ChampionArray_new (
	MemProc *mp,
	HeroClient *heroClient
) {
	ChampionArray *this;

	if ((this = calloc (1, sizeof(ChampionArray))) == NULL)
		return NULL;

	if (!ChampionArray_init (this, mp, heroClient)) {
		ChampionArray_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated ChampionArray structure.
 * ChampionArray *this : An allocated ChampionArray to initialize.
 * HeroClient *heroClient : The HeroClient instance
 * MemProc *mp : The target LoL process
 */
bool
ChampionArray_init (
	ChampionArray *this,
	MemProc *mp,
	HeroClient *heroClient
) {
	Buffer *championArrayEnd = NULL;

	unsigned char pattern[] =
	/*	A1 8808CA03       mov eax, [dword ds:League_of_Legends.HeroClientInstance]
		47                inc edi
		8B15 F058C803     mov edx, [dword ds:League_of_Legends.ChampionArrayEnd]
		83C6 04           add esi, 4
		3BF2              cmp esi, edx
	*/  {
		'?', '_', '_', '_', '_',
		0x47,
		0x8B, '?', '?', '?', '?', '?',
		0x83, 0xC6, 0x04,
		0x3B, 0xF2
	};

	// Put HeroClientInstance address in the pattern
	int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &heroClient->thisStaticPtr, 4);

	// Find a reference to ChampionArrayEnd
	BbQueue *results = memscan_search (mp, "ChampionArrayEnd",
		pattern,
		"?xxxx"
		"x"
		"x?????"
		"xxx"
		"xx",

		"xxxxx"
		"x"
		"xx????"
		"xxx"
		"xx"
	);

	if (results && (championArrayEnd = bb_queue_pick_first(results))) {
		// heroClientInstance has been found
		this->pThis = read_memory_as_int (mp->proc, *((DWORD *) championArrayEnd->data)) - 4;
		dbg ("championArrayEnd found : 0x%08X", this->pThis);

		// We don't need results anymore
		bb_queue_free_all (results, buffer_free);

		return true;
	}

	return true;
}


/*
 * Description : Free an allocated ChampionArray structure.
 * ChampionArray *this : An allocated ChampionArray to free.
 */
void
ChampionArray_free (
	ChampionArray *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
