// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "Position/Position.h"

// ---------- Defines -------------


// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _GUIMinimap
{
	int field_0;
	char gap_4[168];
	int field_1;
	int field_2;
	int field_3;
	int field_4;
	char gap_BC[32];
	Position screenPosition;
	int field_10;
	int field_12;
	char gap_F0[2088];
	int field_14;

	DWORD pThis;

}	GUIMinimap;
#pragma pack(pop)



// --------- Allocators ---------

/*
 * Description 	: Allocate a new GUIMinimap structure.
 * DWORD pGuiMinimap : Address of the GUIMinimap in the target process
 * Return		: A pointer to an allocated GUIMinimap.
 */
GUIMinimap *
GUIMinimap_new (
	DWORD pGuiMinimap
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated GUIMinimap structure.
 * GUIMinimap *this : An allocated GUIMinimap to initialize.
 * DWORD pGuiMinimap : Address of the GUIMinimap in the target process
 */
bool
GUIMinimap_init (
	GUIMinimap *this,
	DWORD pGuiMinimap
);

/*
 * Description : Unit tests checking if a GUIMinimap is coherent
 * GUIMinimap *this : The instance to test
 * Return : true on success, false on failure
 */
bool
GUIMinimap_test (
	GUIMinimap *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated GUIMinimap structure.
 * GUIMinimap *this : An allocated GUIMinimap to free.
 */
void
GUIMinimap_free (
	GUIMinimap *this
);


