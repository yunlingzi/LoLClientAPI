// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef enum _MaestroMessageType {

	MAESTRO_SHUTDOWN = 1,
	MAESTRO_GAME_ABANDONNED = 7,
	MAESTRO_GAME_LAUNCHED = 8,
	MAESTRO_GAME_VERSION_MISMATCH = 9,
	MAESTRO_GAME_CONNECTED_TO_SERVER = 10,
	MAESTRO_CHAT = 12

} 	MaestroMessageType;

typedef struct _MaestroMessageAgent
{




}	MaestroMessageAgent;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new MaestroMessageAgent structure.
 * Return		: A pointer to an allocated MaestroMessageAgent.
 */
MaestroMessageAgent *
MaestroMessageAgent_new (void);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated MaestroMessageAgent structure.
 * MaestroMessageAgent *this : An allocated MaestroMessageAgent to initialize.
 */
bool
MaestroMessageAgent_init (
	MaestroMessageAgent *this
);

/*
 * Description : Unit tests checking if a MaestroMessageAgent is coherent
 * MaestroMessageAgent *this : The instance to test
 * Return : true on success, false on failure
 */
bool
MaestroMessageAgent_test (
	MaestroMessageAgent *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated MaestroMessageAgent structure.
 * MaestroMessageAgent *this : An allocated MaestroMessageAgent to free.
 */
void
MaestroMessageAgent_free (
	MaestroMessageAgent *this
);


