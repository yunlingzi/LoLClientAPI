// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Position/Position.h"
#include "LoLAPIRequest.h"


// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _GamePositionPacket{
	Position pos;

}	GamePositionPacket;

typedef struct _ScreenPositionPacket
{
	int x, y;
}	ScreenPositionPacket;

typedef struct _AnglePacket{
	float y;
	float x;

}	AnglePacket;

typedef struct _FloatPacket{
	float value;

}	FloatPacket;

typedef struct _BytePacket{
	byte value;

}	BytePacket;

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
	bool value;

}	BooleanPacket;


typedef struct _LoLAPIPacket
{
	LoLAPIRequest request;

	union {
		GamePositionPacket gamePositionPacket;
		ScreenPositionPacket screenPositionPacket;
		AnglePacket anglePacket;
		FloatPacket floatPacket;
		IntPacket intPacket;
		BytePacket bytePacket;
		StringPacket stringPacket;
		HpPacket hpPacket;
		BooleanPacket booleanPacket;
	};

	int teammateId;

}	LoLAPIPacket;
