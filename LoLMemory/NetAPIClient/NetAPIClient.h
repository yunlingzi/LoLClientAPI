// --- Author : Moreau Cyril - Spl3en <spl3en.contact@gmail.com>
#pragma once

// ---------- Includes ------------
#include "MemProc/MemProc.h"

// ---------- Defines -------------

// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _NetAPIClient
{
	int field_0;
	int field_1;
	int field_3;
	int field_5;
	int field_6;
	int field_7;
	char gap_18[72];
	int spectatorGameTime;

	DWORD pThis;

} NetAPIClient;
#pragma pack(pop)



// --------- Constructors ---------

/*
 * Description 	: Allocate a new NetAPIClient structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated NetAPIClient.
 */
NetAPIClient *
NetAPIClient_new (
	MemProc *mp
);


// ----------- Functions ------------

/*
 * Description : Initialize an allocated NetAPIClient structure.
 * NetAPIClient *this : An allocated NetAPIClient to initialize.
 * MemProc *mp : The target LoL process
 * Return : true on success, false on failure.
 */
bool
NetAPIClient_init (
	NetAPIClient *this,
	MemProc *mp
);

/*
 * Description : Unit tests checking if a NetAPIClient is coherent
 * NetAPIClient *this : The instance to test
 * Return : true on success, false on failure
 */
bool
NetAPIClient_test (
	NetAPIClient *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated NetAPIClient structure.
 * NetAPIClient *this : An allocated NetAPIClient to free.
 */
void
NetAPIClient_free (
	NetAPIClient *this
);


