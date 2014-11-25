#include "ChampionArray.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "ChampionArray"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new ChampionArray structure.
 * HeroClient *heroClient : The HeroClient instance
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated ChampionArray.
 */
ChampionArray *
ChampionArray_new (
	HeroClient *heroClient,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	ChampionArray *this;

	if ((this = calloc (1, sizeof(ChampionArray))) == NULL)
		return NULL;

	if (!ChampionArray_init (this, heroClient, baseAddress, sizeOfModule)) {
		ChampionArray_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated ChampionArray structure.
 * ChampionArray *this : An allocated ChampionArray to initialize.
 * HeroClient *heroClient : The HeroClient instance
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
ChampionArray_init (
	ChampionArray *this,
	HeroClient *heroClient,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	this->heroClient = heroClient;

	unsigned char pattern[] =
	/*	A1 8808CA03       mov eax, [dword ds:League_of_Legends.HeroClientInstance]
		47                inc edi
		8B15 F058C803     mov edx, [dword ds:League_of_Legends.ChampionArrayEnd]
		83C6 04           add esi, 4
		3BF2              cmp esi, edx
	*/  {
		'?', '_', '_', '_', '_',
		'?',
		0x8B, '?', '?', '?', '?', '?',
		0x83, 0xC6, 0x04,
		0x3B, 0xF2
	};

	// Put HeroClientInstance address in the pattern
	int replacePos = str_n_pos (pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &heroClient->thisStatic, 4);

	// Find a reference to ChampionArrayEnd
	DWORD championArrayEnd = mem_scanner ("ChampionArrayEnd",
		baseAddress, sizeOfModule,
		pattern,
		"?xxxx"
		"?"
		"??????"
		"xxx"
		"??",

		"xxxxx"
		"x"
		"xx????"
		"xxx"
		"xx"
	);

	if (championArrayEnd)
	{
		DWORD championArrayStart = championArrayEnd - 4;

		// championArrayEnd has been found
		this->pThis = championArrayStart;
		dbg ("championArray found : 0x%08X", this->pThis);

		// Allocate champion array
		this->start = *((DWORD *) championArrayStart);
		this->end   = *((DWORD *) championArrayEnd);

		this->championsCount = (this->end - this->start) / 4;
		this->champions = malloc (sizeof(Unit *) * this->championsCount);
		this->teammates = malloc (sizeof(Unit *) * this->championsCount);

		// Initialize champion array
		for (DWORD cur = this->start, pos = 0; cur != this->end; cur += 4, pos++) {
			this->champions[pos] = Unit_new (cur);
			this->teammates[pos] = NULL;
		}

		// Count teammates later
		this->teammatesCount = 0;

		int teammateId = 0;
		for (int curChampionIndex = 0; curChampionIndex < this->championsCount; curChampionIndex++)
		{
			Unit * champion = this->champions[curChampionIndex];

			if (heroClient->pThis == 0 || (
				(champion->pThis != heroClient->pThis)
			&&  (champion->team  == heroClient->team))) {
				// Champion-team and self-team is the same : They are teammates
				this->teammates[teammateId] = champion;
				this->teammatesCount++;
				champion->teammateId = teammateId++;
			}
		}

		return true;
	}

	dbg ("ChampionArray not found.");

	return false;
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
