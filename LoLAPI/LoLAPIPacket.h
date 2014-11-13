// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Position/Position.h"

// ---------- Defines -------------


// ------ Structure declaration -------

typedef struct _PositionPacket{
	Position position;

}	PositionPacket;

typedef struct _AnglePacket{
	float y;
	float x;

}	AnglePacket;

typedef struct _FloatPacket{
	float value;

}	FloatPacket;

typedef struct _IntPacket
{
	int value;

}	IntPacket;

typedef struct _StringPacket
{
	char str [16];

} 	StringPacket;

typedef struct _HpPacket
{
	float curHP;
	float maxHP;

}	HpPacket;

typedef struct _BooleanPacket{
	bool boolean;

}	BooleanPacket;
