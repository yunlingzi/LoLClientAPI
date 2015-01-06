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

typedef enum _TeamId {
	TEAM_BLUE    = 0,
	TEAM_PURPLE  = 1,
	TEAM_UNKNOWN = 2
} TeamId;

// ------ Structure declaration -------
// HeroClient inherits everything from HeroClient structure
typedef Unit HeroClient;

// --------- Allocators ---------

/*
 * Description 	: Allocate a new HeroClient structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated HeroClient.
 */
HeroClient *
HeroClient_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);


// ----------- Functions ------------

/*
 * Description : Initialize an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
HeroClient_init (
	HeroClient *this,
	DWORD baseAddress,
	DWORD sizeOfModule
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


