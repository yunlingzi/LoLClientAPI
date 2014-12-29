// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "LoLMemory/HudManager/HudManager.h"
#include "LoLMemory/HeroClient/HeroClient.h"
#include "LoLMemory/ChampionArray/ChampionArray.h"
#include "LoLMemory/GUIMenu/GUIMenu.h"
#include "LoLMemory/NetAPIClient/NetAPIClient.h"
#include "LoLMemory/GameClock/GameClock.h"
#include "LoLMemory/HudChat/HudChat.h"
#include "MemProc/MemProc.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _LoLModule
{
    DWORD baseAddress;

	// Memory structures
	HudManager *hudManager;
	HeroClient *heroClient;
	ChampionArray *championArray;
	GUIMenu *guiMenu;
	NetAPIClient *netApiClient;
	GameClock *gameClock;
	HudChat *hudChat;

}	LoLModule;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new LoLModule structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated LoLModule.
 */
LoLModule *
LoLModule_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated LoLModule structure.
 * LoLModule *this : An allocated LoLModule to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
LoLModule_init (
	LoLModule *this,
	DWORD baseAddress,
	DWORD sizeOfModule
);

/*
 * Description : Unit tests checking if a LoLModule is coherent
 * LoLModule *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLModule_test (
	LoLModule *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated LoLModule structure.
 * LoLModule *this : An allocated LoLModule to free.
 */
void
LoLModule_free (
	LoLModule *this
);



