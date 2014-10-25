// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.39.29
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"


// ---------- Defines -------------


// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _Position
{
	float x;
	float z;
	float y;
}	Position;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _Position2D
{
	int x;
	int y;
}	Position2D;
#pragma pack(pop)



// --------- Constructors ---------

Position *
Position_new (float x, float y, float z);

Position *
Position_alloc (void);

// ----------- Functions ------------

void
Position_init (Position *Position, float x, float y, float z);

bool
Position_in_map (Position *this);

// --------- Destructors ----------

void
Position_free (Position *Position);



