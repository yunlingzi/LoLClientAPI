#include "GameClock.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "GameClock"
#include "dbg/dbg.h"


/*
 * Description 	      : Allocate a new GameClock structure.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return             : A pointer to an allocated GameClock.
 */
GameClock *
GameClock_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	GameClock *this;

	if ((this = calloc(1, sizeof(GameClock))) == NULL)
		return NULL;

	if (!GameClock_init (this, baseAddress, sizeOfModule)) {
		GameClock_free (this);
		return NULL;
	}

	return this;
}

/*
 * Description        : Initialize an allocated GameClock structure.
 * GameClock *this    : An allocated GameClock to initialize.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return             : true on success, false on failure.
 */
bool
GameClock_init (
	GameClock *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	unsigned char pattern[] = {
		/*	8B0D A891D503     mov ecx, [dword ds:League_of_Legends.GameClockInstance]
			8B01              mov eax, [dword ds:ecx]
			8B40 08           mov eax, [dword ds:eax+8]
			FFD0              call eax
			51                push ecx
			DDD8              fstp st 	*/
			0x8B, 0x0D, '?', '?', '?', '?',
			0x8B, 0x01,
			0x8B, 0x40, 0x08,
			0xFF, 0xD0,
			0x51,
			0xDD, 0xD8
	};

	// Find a reference to GameClockInstance
	DWORD gameClockInstance = mem_scanner ("GameClockInstance",
		baseAddress, sizeOfModule,
		pattern,

		"xx????"
		"xx"
		"xxx"
		"xx"
		"x"
		"xx",

		"xx????"
		"xx"
		"xxx"
		"xx"
		"x"
		"xx"
	);

	if (!gameClockInstance) {
		dbg ("GameClockInstance not found");
		return false;
	}

	// gameClockInstance has been found
	dbg ("GameClockInstance found : 0x%08X", gameClockInstance);
	this->pThis = *((DWORD *) gameClockInstance);

	return true;
}


/*
 * Description     : Free an allocated GameClock structure.
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
