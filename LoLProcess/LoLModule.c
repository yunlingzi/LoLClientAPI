#include "LoLModule.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "LoLModule"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new LoLModule structure.
 * Return		: A pointer to an allocated LoLModule.
 */
LoLModule *
LoLModule_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	LoLModule *this;

	if ((this = calloc (1, sizeof(LoLModule))) == NULL)
		return NULL;

	if (!LoLModule_init (this, baseAddress, sizeOfModule)) {
		LoLModule_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated LoLModule structure.
 * LoLModule *this : An allocated LoLModule to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
LoLModule_init (
	LoLModule *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	this->baseAddress = baseAddress;

	// Get a copy of the current client memory - base module only
	dbg ("Scanning the image base module ... (0x%08X)", baseAddress);

	// Initialize the Hud Manager
	if (!(this->hudManager = HudManager_new (baseAddress, sizeOfModule))) {
		dbg ("Cannot get hudManager.");
		return false;
	}

	// Initialize the heroClient
	if (!(this->heroClient = HeroClient_new (baseAddress, sizeOfModule))) {
		dbg ("Cannot get heroClient.");
	}

	// Initialize the championArray
	if (!(this->championArray = ChampionArray_new (this->heroClient, baseAddress, sizeOfModule))) {
		dbg ("Cannot get championArray.");
	}

	// Initialize the GUI Menu
	if (!(this->guiMenu = GUIMenu_new (baseAddress, sizeOfModule))) {
		dbg ("Cannot get GUIMenu.");
		return false;
	}

	// Initialize GameClock
	if (!(this->gameClock = GameClock_new (baseAddress, sizeOfModule))) {
		dbg ("Cannot get GameClock.");
		return false;
	}

	return true;
}


/*
 * Description : Free an allocated LoLModule structure.
 * LoLModule *this : An allocated LoLModule to free.
 */
void
LoLModule_free (
	LoLModule *this
) {
	if (this != NULL)
	{
		HudManager_free (this->hudManager);
		HeroClient_free (this->heroClient);
		ChampionArray_free (this->championArray);
		GUIMenu_free (this->guiMenu);
		NetAPIClient_free (this->netApiClient);
		GameClock_free (this->gameClock);

		free (this);
	}
}


/*
 * Description : Unit tests checking if a LoLModule is coherent
 * LoLModule *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLModule_test (
	LoLModule *this
) {
	bool result = true;

	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	if (!HudManager_test (this->hudManager)) {
		fail ("HudManager test failed.");
		result = false;
	}
	else {
		dbg ("[OK] HudManager test success.");
	}

	if (!HeroClient_test (this->heroClient)) {
		fail ("HeroClient test failed.");
		result = false;
	}
	else {
		dbg ("[OK] HeroClient test success.");
	}

	if (!ChampionArray_test (this->championArray)) {
		fail ("ChampionArray test failed.");
		result = false;
	}
	else {
		dbg ("[OK] ChampionArray test success.");
	}

	if (!GUIMenu_test (this->guiMenu)) {
		fail ("GUIMenu unit test failed.");
		result = false;
	}
	else {
		dbg ("[OK] GUIMenu test success.");
	}

	return result;
}
