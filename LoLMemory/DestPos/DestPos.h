// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "Position/Position.h"
#include "MemProc/MemProc.h"
#include "Scanner/Scanner.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _DestPos
{
	Position serverDestPosition;
	Position clientDestPosition;

	DWORD pThis;

}	DestPos;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new DestPos structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated DestPos.
 */
DestPos *
DestPos_new (
	MemProc *mp
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated DestPos structure.
 * DestPos *this : An allocated DestPos to initialize.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return : true on success, false on failure.
 */
bool
DestPos_init (
	DestPos *this,
	MemProc *mp
);

/*
 * Description : Unit tests checking if a DestPos is coherent
 * DestPos *this : The instance to test
 * Return : true on success, false on failure
 */
bool
DestPos_test (
	DestPos *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated DestPos structure.
 * DestPos *this : An allocated DestPos to free.
 */
void
DestPos_free (
	DestPos *this
);


