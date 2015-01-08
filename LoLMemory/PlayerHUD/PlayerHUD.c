#include "PlayerHUD.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "PlayerHUD"
#include "dbg/dbg.h"

/*
 * Description 	      : Allocate a new PlayerHUD structure.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return             : A pointer to an allocated PlayerHUD.
 */
PlayerHUD *
PlayerHUD_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	PlayerHUD *this;

	if ((this = calloc (1, sizeof(PlayerHUD))) == NULL)
		return NULL;

	if (!PlayerHUD_init (this, baseAddress, sizeOfModule)) {
		PlayerHUD_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description        : Initialize an allocated PlayerHUD structure.
 * PlayerHUD *this    : An allocated PlayerHUD to initialize.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return             : true on success, false on failure.
 */
bool
PlayerHUD_init (
	PlayerHUD *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	/* Not far from the strings :
		game_spellcaststatus_outofmana
		game_spellcaststatus_cooldown
		game_spellcaststatus_disabled
		game_spellcaststatus_notlearned
	*/
	unsigned char pattern[] = {
		/*  57                     push edi
			8B3D 1C908C01          mov edi, [playerHUDInstance]
			83F8 03                cmp eax, 3
			77 6F                  ja short League_of_Legends.default
			FF2485 54AF6600        jmp [dword ds:eax*4+League_of_Legends.switchTable]
		*/
			0x57,
			0x8B, 0x3D, '?', '?', '?', '?',
			0x83, 0xF8, 0x03,
			0x77, '?',
			0xFF, 0x24, 0x85, '?', '?', '?', '?'
	};

	// Find a reference to GameClockInstance
	DWORD playerHUDInstance = mem_scanner ("playerHUDInstance",
		baseAddress, sizeOfModule,
		pattern,
		"x"
		"xx????"
		"xxx"
		"x?"
		"xxx????",

		"x"
		"xx????"
		"xxx"
		"xx"
		"xxxxxxx"
	);

	if (!playerHUDInstance) {
		dbg ("playerHUDInstance not found");
		return false;
	}

	// playerHUDInstance has been found
	dbg ("playerHUDInstance found : 0x%08X", playerHUDInstance);
	memcpy (this, *((DWORD **) playerHUDInstance), sizeof(PlayerHUD));
	this->pThis = *((DWORD *) playerHUDInstance);

	// Instanciate playerHudChat
	if ((this->hudChat = HudChat_new (baseAddress, sizeOfModule, (DWORD) this->hudChat)) == NULL) {
		warn ("HudChat not found.");
		return false;
	}

	return true;
}


/*
 * Description     : Free an allocated PlayerHUD structure.
 * PlayerHUD *this : An allocated PlayerHUD to free.
 */
void
PlayerHUD_free (
	PlayerHUD *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description     : Unit tests checking if a PlayerHUD is coherent
 * PlayerHUD *this : The instance to test
 * Return          : true on success, false on failure
 */
bool
PlayerHUD_test (
	PlayerHUD *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	return true;
}
