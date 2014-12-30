// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "EasySocket/EasySocket.h"
#include "LoLAPI/LoLAPI.h"
#include "LoLAPI/LoLAPIPacket.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef enum _LoLClientAPIError
{
	API_NO_ERROR,
	API_SEND_ERROR,
	API_RECV_ERROR,
	API_REQUEST_FAIL,
	API_REQUEST_INVALID,
	API_REQUEST_UNSYNCHRONIZED

} LoLClientAPIError;

typedef struct _LoLClientAPI
{
	EasySocket * clientSocket;
	bool ready;

	LoLClientAPIError lastError;

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

/*
 * Description : Receive packet from the LoLServerAPI
 * LoLClientAPI *this : An allocated LoLClientAPI
 * LoLAPIPacket *packet : A packet to recieve
 * int packetSize : The size of the packet
 * Return : bool true on success, false otherwise
 */
bool
LoLClientAPI_recv (
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


