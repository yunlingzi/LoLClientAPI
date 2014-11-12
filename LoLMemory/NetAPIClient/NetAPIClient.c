#include "NetAPIClient.h"
#include "LoLClientAPI.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "NetAPIClient"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new NetAPIClient structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated NetAPIClient.
 */
NetAPIClient *
NetAPIClient_new (
	MemProc *mp
) {
	NetAPIClient *this;

	if ((this = calloc(1, sizeof(NetAPIClient))) == NULL)
		return NULL;

	if (!NetAPIClient_init (this, mp)) {
		NetAPIClient_free (this);
		return NULL;
	}

	return this;
}

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
) {
	MemBlock *mb = NULL;
	Buffer *pNetAPIClientInstance = NULL;

	BbQueue *results = memscan_search_string (
		mp, "NetAPIClientInstanceStr",
		"NetAPI::GetClient: Client pointer not created yet"
	);

	if (!results) {
		dbg ("NetAPIClientInstanceStr not found.");
		return false;
	}

	if ((mb = bb_queue_pick_first(results))) {
		// NetAPIClientInstanceStr has been found

		dbg ("NetAPIClientInstanceStr found : 0x%08X", mb->addr);

		unsigned char pattern[] = {
		/*	8B0D 3061D403   mov ecx, [dword ds:League_of_Legends.3D46130]
			85C9            test ecx, ecx
			75 27           jnz short League_of_Legends.0151EA6A
			68 30930402     push offset League_of_Legends.02049330        ; ASCII "NetAPI::GetClient: Client pointer not created yet!"
			68 78930402     push offset League_of_Legends.02049378        ; ASCII "NetAPI::GetClient"
			68 4F080000     push 84F
			68 188A0402     push offset League_of_Legends.02048A18
			68 8C930402     push offset League_of_Legends.0204938C        ; ASCII "(spMultiplayerClient != NULL)"
			E8 7FCF4200     call League_of_Legends.0194B9E0 */
			0x8B, 0x0D, '?', '?', '?', '?',
			0x85, 0xC9,
			0x75, '?',
			0x68, '_', '_', '_', '_',
			0x68, '?', '?', '?', '?',
			0x68, '?', '?', '?', '?',
			0x68, '?', '?', '?', '?',
			0x68, '?', '?', '?', '?',
			0xE8, '?', '?', '?', '?'
		};

		// Replace ____ with pNetAPIClientInstance address
		int replacePos = str_n_pos(pattern, "____", sizeof(pattern));
		memcpy(&pattern[replacePos], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to NetAPIClientAddress
		results = memscan_search (mp, "pNetAPIClientInstance",
			pattern,
			"xx????"
			"xx"
			"x?"
			"xxxxx"
			"x????"
			"x????"
			"x????"
			"x????"
			"x????",

			"xx????"
			"xx"
			"xx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"

		);

		if (results && (pNetAPIClientInstance = bb_queue_pick_first(results))) {
			// pNetAPIClientInstance has been found
			this->pThis = read_memory_as_int (mp->proc, *((DWORD *)pNetAPIClientInstance->data));
			dbg ("pNetAPIClient pointer found : 0x%08X", this->pThis);

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);

			return true;
		}
	}

	return false;
}


/*
 * Description : Free an allocated NetAPIClient structure.
 * NetAPIClient *this : An allocated NetAPIClient to free.
 */
void
NetAPIClient_free (
	NetAPIClient *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
