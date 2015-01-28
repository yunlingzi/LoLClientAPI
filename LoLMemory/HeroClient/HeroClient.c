#include "HeroClient.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HeroClient"
#include "dbg/dbg.h"


/*
 * Description 	      : Allocate a new HeroClient structure.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return             : A pointer to an allocated HeroClient.
 */
HeroClient *
HeroClient_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	HeroClient *this;

	if ((this = calloc (1, sizeof(HeroClient))) == NULL)
		return NULL;

	if (!HeroClient_init (this, baseAddress, sizeOfModule)) {
		HeroClient_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description        : Initialize an allocated HeroClient structure.
 * HeroClient *this   : An allocated HeroClient to initialize.
 * DWORD baseAddress  : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
HeroClient_init (
	HeroClient *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	bool correctHeroClientStr = false;
	DWORD heroClientStr = NULL;
	DWORD currentAddress = baseAddress;
	DWORD currentSizeOfModule = sizeOfModule;

	// Find the correct instance of "MINIONS_KILLED"
	while (!correctHeroClientStr) {
		correctHeroClientStr = true;

		heroClientStr = memscan_string (
			"HeroClientStr",
			currentAddress, currentSizeOfModule,
			"MINIONS_KILLED"
		);

		if (heroClientStr) {
			if (*(char *)(heroClientStr - 1) == '"') {
				// The debug string '[..].GetHeroStat("MINIONS_KILLED")->[...]' also exists in the binary
				correctHeroClientStr = false;
			}

			else if (*(char *)(heroClientStr - 1) == '_') {
				// NEUTRAL_MINIONS_KILLED also exists in the binary
				correctHeroClientStr = false;
			}

			currentSizeOfModule = currentSizeOfModule - (heroClientStr - currentAddress + 1);
			currentAddress = heroClientStr + 1;
		}
	}

	if (!heroClientStr) {
		fail ("HeroClientStr not found.");
		return false;
	}

	// HeroClientStr has been found
	dbg ("HeroClientStr found : 0x%08X", heroClientStr);

	unsigned char pattern [] = {
		/*	68 FCEC1F01       push offset League_of_Legends.011FECFC        ; ASCII "MINIONS_KILLED"
            8D8C24 B0000000   lea ecx, [esp+0B0]
            E8 54DB1700       call League_of_Legends.008B3820
            C78424 E8000000 0 mov [dword ss:esp+0E8], 0
            8D8424 AC000000   lea eax, [esp+0AC]
            8B0D A4874901     mov ecx, [dword ds:League_of_Legends.14987A4] */
            0x68, '_',  '_',  '_',  '_',
            0x8D, '?', '?', '?',  '?',  '?',  '?',
            0xE8, '?', '?', '?', '?',
            0xC7, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
            0x8D, '?', '?', '?', '?', '?', '?',
            0x8B, '?', '?', '?', '?', '?'
	};

	// Replace ____ with HeroClientStr address
	int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &heroClientStr, 4);

	// Find a reference to HeroClient
	DWORD heroClientInstance = mem_scanner ("HeroClientInstance",
		baseAddress, sizeOfModule,
		pattern,

        "xxxxx"
        "x??????"
        "x????"
        "x??????????"
        "x??????"
        "x?????",

        "xxxxx"
        "xxxxxxx"
        "xxxxx"
        "xxxxxxxxxxx"
        "xxxxxxx"
        "xx????"
	);

	if (heroClientInstance)
	{
		// heroClientInstance has been found
		dbg ("HeroClientInstance found : 0x%08X", heroClientInstance);

		Unit_init (this, heroClientInstance);

		if (!this->pThis) {
			// We cannot conclude an error occurred because it is a normal behavior in spectator mode
			warn ("HeroClientInstance not initialized. Are you in spectator mode ?");
		}

		return true;
	}

	dbg ("HeroClientInstance not found.");

	return false;
}


/*
 * Description      : Free an allocated HeroClient structure.
 * HeroClient *this : An allocated HeroClient to free.
 */
void
HeroClient_free (
	HeroClient *this
) {
	if (this != NULL)
	{
		free (this);
	}
}

