#include "GUIMenu.h"
#include "LoLProcess/LoLProcess.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "GUIMenu"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new GUIMenu structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated GUIMenu.
 */
GUIMenu *
GUIMenu_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	GUIMenu *this;

	if ((this = calloc (1, sizeof(GUIMenu))) == NULL)
		return NULL;

	if (!GUIMenu_init (this, baseAddress, sizeOfModule)) {
		GUIMenu_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated GUIMenu structure.
 * GUIMenu *this : An allocated GUIMenu to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
GUIMenu_init (
	GUIMenu *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	DWORD GUIMenuStr = memscan_string (
		"GUIMenuStr",
		baseAddress, sizeOfModule,
		"GAMESTATE_GAMELOOP GUIMenuDraw"
	);

	if (!GUIMenuStr) {
		dbg ("GUIMenuStr not found.");
		return false;
	}

	// HudManagerInstanceStr has been found
	dbg ("GUIMenuStr found : 0x%08X", GUIMenuStr);

	unsigned char pattern[] = {
		/*	68 A41C0902       push offset League_of_Legends.02091CA4                   ; ASCII "GAMESTATE_GAMELOOP GUIMenuDraw\n"
			FF35 D47E4A02     push [dword ds:League_of_Legends.24A7ED4]
			83C8 01           or eax, 00000001
			50                push eax
			6A 03             push 3
			E8 F305ECFF       call League_of_Legends.015DA170
			83C4 10           add esp, 10
			833D 547ED503 00  cmp [dword ds:League_of_Legends.GUIMenuInstance], 0 */
		0x68, '_', '_', '_', '_',
		'?', '?', '?', '?', '?', '?',
		'?', '?', '?',
		'?',
		'?', 0x03,
		0xE8, '?', '?', '?', '?',
		'?', '?', '?',
		'?', '?', '?', '?', '?', '?', 0x00
	};

	// Replace ____ with pHudManagerInstance address
	int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &GUIMenuStr, 4);

	// Find a reference to GUIMenuInstance
	DWORD GUIMenuInstance = mem_scanner ("GUIMenuInstance",
		baseAddress, sizeOfModule,
		pattern,

		"xxxxx"
		"??????"
		"???"
		"?"
		"?x"
		"x????"
		"???"
		"??????x",

		"xxxxx"
		"xxxxxx"
		"xxx"
		"x"
		"xx"
		"xxxxx"
		"xxx"
		"xx????x"
	);

	if (GUIMenuInstance)
	{
		// GUIMenuInstance has been found
		dbg ("GUIMenuInstance found : 0x%08X", GUIMenuInstance);

		// Initialize GUIMenu
		memcpy (this, *((DWORD **) GUIMenuInstance), sizeof(GUIMenu));
		this->pThis = *((DWORD *) GUIMenuInstance);
		this->pStaticThis = GUIMenuInstance;

		// Initialize guiMinimap structure
		if (!(this->guiMinimap = GUIMinimap_new ((DWORD) this->guiMinimap))) {
			dbg ("Cannot get guiMinimap.");
			return false;
		}

		return true;
	}

	dbg ("GUIMenuInstance not found.");

	return false;
}


/*
 * Description : Free an allocated GUIMenu structure.
 * GUIMenu *this : An allocated GUIMenu to free.
 */
void
GUIMenu_free (
	GUIMenu *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
