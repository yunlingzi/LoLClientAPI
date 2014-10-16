// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "MemProc/MemProc.h"
#include "Scanner/Scanner.h"
#include "Position/Position.h"

// ---------- Defines -------------


// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HeroClient
{
	int field_0;
	char gap_4[20];
	int team;
	char gap_1C[8];
	char summonerName[16];
	char gap_34[44];
	Position position;
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
	int maxHP;
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

}	HeroClient;
#pragma pack(pop)

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


