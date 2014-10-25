// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "Position/Position.h"
#include "MemProc/MemProc.h"

// ---------- Defines -------------


// ------ Structure declaration -------

#pragma pack(push, 1)
typedef struct _Unit
{
	int field_0;
	char gap_4[20];
	int team;
	char gap_1C[8];
	char summonerName[16];
	char gap_34[44];
	Position currentPosition;
	char gap_6C[168];
	int field_1;
	int field_2;
	int field_3;
	int field_4;
	char gap_124[4];
	int field_5;
	char gap_12C[4];
	int field_6;
	int field_7;
	float curHP;
	int field_13C;
	int field_140;
	int field_144;
	float maxHP;
	char gap_14C[632];
	int field_8;
	int field_9;
	int field_10;
	int field_11;
	int field_12;
	int field_13;
	char gap_3DC[4];
	int field_14;
	char gap_3E4[4];
	int field_15;
	char gap_3EC[4];
	int field_16;
	char gap_3F4[4];
	int field_17;
	char gap_3FC[4];
	int field_18;
	char gap_404[4];
	int field_19;
	char gap_40C[4];
	int field_20;
	char gap_414[4];
	int field_21;
	char gap_41C[4];
	int field_22;
	char gap_424[4];
	int field_23;
	char gap_42C[4];
	int field_24;
	char gap_434[4];
	int field_25;
	char gap_43C[4];
	int field_26;
	char gap_444[4];
	int field_27;
	int field_28;
	char gap_450[7640];
	int field_29;

	DWORD pThis;
	DWORD thisStaticPtr;
	int teammateId;

}	Unit;
#pragma pack(pop)



// --------- Allocators ---------

/*
 * Description 	: Allocate a new Unit structure.
 * DWORD pUnit : The address of the Unit in the target process
 * MemProc *mp  : Handle to the target process
 * Return		: A pointer to an allocated Unit.
 */
Unit *
Unit_new (
	MemProc *mp,
	DWORD pUnit
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated Unit structure.
 * Unit *this : An allocated Unit to initialize.
 * DWORD pUnit : The address of the Unit in the target process
 * MemProc *mp  : Handle to the target process
 */
bool
Unit_init (
	Unit *this,
	MemProc *mp,
	DWORD pUnit
);


/*
 * Description : Unit tests checking if a Unit is coherent
 * Unit *this : The instance to test
 * Return : true on success, false on failure
 */
bool
Unit_test (
	Unit *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated Unit structure.
 * Unit *this : An allocated Unit to free.
 */
void
Unit_free (
	Unit *this
);


