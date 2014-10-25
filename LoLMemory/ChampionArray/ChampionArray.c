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
		// championArrayEnd has been found
		this->pThis = *((DWORD *) championArrayEnd->data) - 4;
		dbg ("championArray found : 0x%08X", this->pThis);

		// We don't need results anymore
		bb_queue_free_all (results, buffer_free);

		// Allocate champion array
		this->start = read_memory_as_int (mp->proc, this->pThis);
		this->end   = read_memory_as_int (mp->proc, this->pThis + 4);

		this->championsCount = (this->end - this->start) / 4;
		this->champions = malloc (sizeof(Unit *) * this->championsCount);

		// Initialize champion array
		for (DWORD cur = this->start, pos = 0; cur != this->end; cur += 4, pos++) {
			this->champions[pos] = Unit_new (mp, read_memory_as_int(mp->proc, cur));
		}

		// Count teammates later
		this->teammatesCount = -1;

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
