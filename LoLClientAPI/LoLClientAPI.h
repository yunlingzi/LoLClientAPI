// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "EasySocket/EasySocket.h"
#include "LoLAPI/LoLAPI.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _LoLClientAPI
{
	EasySocket * clientSocket;
	bool closed;

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

// --------- Destructors ----------

/*
 * Description : Free an allocated LoLClientAPI structure.
 * LoLClientAPI *this : An allocated LoLClientAPI to free.
 */
void
LoLClientAPI_free (
	LoLClientAPI *this
);


