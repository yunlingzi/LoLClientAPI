// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "MemProc/MemProc.h"
#include "Scanner/Scanner.h"
#include "LoLMemory/Unit/Unit.h"

// ---------- Defines -------------
#define CLIENT_TEAM_BLUE	0x64
#define CLIENT_TEAM_PURPLE	0xC8
#define TEAM_BLUE	0
#define TEAM_PURPLE	1
#define TEAM_UNKNOWN 2


// ------ Structure declaration -------
// HeroClient inherits everything from HeroClient structure
typedef Unit HeroClient;

// --------- Allocators ---------

/*
 * Description 	: Allocate a new HeroClient structure.
 * MemProc *mp : The target LoL process
 * Return		: A pointer to an allocated HeroClient.
 */
HeroClient *
HeroClient_new (
	MemProc *mp
);


// ----------- Functions ------------

/*
 * Description : Initialize an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to initialize.
 */
bool
HeroClient_init (
	HeroClient *this,
	MemProc *mp
);

/*
 * Description : Unit tests checking if a HeroClient is coherent
 * HeroClient *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HeroClient_test (
	HeroClient *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to free.
 */
void
HeroClient_free (
	HeroClient *this
);


