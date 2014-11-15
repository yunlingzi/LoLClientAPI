// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "EasySocket/EasySocket.h"
#include "LoLAPI/LoLAPI.h"
#include "LoLAPI/LoLAPIPacket.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _LoLClientAPI
{
	EasySocket * clientSocket;
	bool closed;
	bool ready;

}	LoLClientAPI;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new LoLClientAPI structure.
 * Return		: A pointer to an allocated LoLClientAPI.
 */
LoLClientAPI *
LoLClientAPI_new (void);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated LoLClientAPI structure.
 * LoLClientAPI *this : An allocated LoLClientAPI to initialize.
 */
bool
LoLClientAPI_init (
	LoLClientAPI *this
);

/*
 * Description : Unit tests checking if a LoLClientAPI is coherent
 * LoLClientAPI *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLClientAPI_test (
	LoLClientAPI *this
);

/*
 * Description : Send to the LoLServerAPI a given request
 * LoLClientAPI *this : An allocated LoLClientAPI
 * LoLAPIPacket *packet : A packet to send
 * int packetSize : The size of the packet
 * Return : bool true on success, false otherwise
 */
bool
LoLClientAPI_send (
	LoLClientAPI *this,
	LoLAPIPacket *packet,
	int packetSize
);

// --------- Destructors ----------

/*
 * Description : Free an allocated LoLClientAPI structure.
 * LoLClientAPI *this : An allocated LoLClientAPI to free.
 */
void
LoLClientAPI_free (
	LoLClientAPI *this
);


