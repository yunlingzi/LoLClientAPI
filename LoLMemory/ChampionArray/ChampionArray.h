// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "MemProc/MemProc.h"
#include "LoLMemory/Unit/Unit.h"
#include "LoLMemory/HeroClient/HeroClient.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _ChampionArray
{
	DWORD start;
	DWORD end;

	DWORD pThis;

	Unit **champions;
	int championsCount;

	Unit **teammates;
	int teammatesCount;

}	ChampionArray;



// --------- Allocators ---------

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
);

// ----------- Functions ------------


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
);


/*
 * Description : Unit tests checking if a ChampionArray is coherent
 * ChampionArray *this : The instance to test
 * Return : true on success, false on failure
 */
bool
ChampionArray_test (
	ChampionArray *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated ChampionArray structure.
 * ChampionArray *this : An allocated ChampionArray to free.
 */
void
ChampionArray_free (
	ChampionArray *this
);


