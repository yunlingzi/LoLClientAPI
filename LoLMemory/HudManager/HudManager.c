#include "HudManager.h"
#include "Scanner/Scanner.h"
#include <stdlib.h>

#define _DEBUG_OBJECT__ "HudManager"

HudManager *
HudManager_new (MemProc *mp)
{
	HudManager *this;

	if ((this = HudManager_alloc()) == NULL)
		return NULL;

	HudManager_init (this, mp);

	return this;
}

HudManager *
HudManager_alloc (void)
{
	return calloc(1, sizeof(HudManager));
}

void
HudManager_init (HudManager *this, MemProc *mp)
{
	MemBlock *mb = NULL;
	Buffer *pHudManagerInstance = NULL;

	BbQueue *results = memscan_search_string (
		mp, "HudManagerInstanceStr",
		"HudManager::GetInstance: Instance not created yet or already destroyed"
	);

	if ((mb = bb_queue_pick_first(results))) {
		// HudManagerInstanceStr has been found

		debug("HudManagerInstanceStr found : 0x%08X", mb->data);

		unsigned char pattern[] =
			/*
				01629DE0     A1 0846BD03       mov eax, [dword ds:League_of_Legends.3BD4608] <--- pHudManagerInstance
				01629DE5     85C0              test eax, eax
				01629DE7   ▼ 75 26             jnz short League_of_Legends.01629E0F
				01629DE9     68 302FF001       push offset League_of_Legends.01F02F30 <-- HudManagerInstanceStr
				01629DEE     68 782FF001       push offset League_of_Legends.01F02F78
				01629DF3     68 74010000       push 174
				01629DF8     68 D82DF001       push offset League_of_Legends.01F02DD8
				01629DFD     68 C826EE01       push offset League_of_Legends.01EE26C8
			*/
			"?????"
			"??"
			"??"
			"\x68____"
			"\x68????"
			"\x68\x74\x01\x00\x00"
			"\x68????"
			"\x68????";

		// Replace ____ with pHudManagerInstance address
		memcpy(&pattern[10], &mb->addr, 4);

		// We don't need results anymore
		bb_queue_free_all (results, memblock_free);

		// Find a reference to HudManagerAddress
		results = memscan_search (mp, "pHudManagerInstance",
			pattern,

			"?????"
			"??"
			"??"
			"xxxxx"
			"x????"
			"xxxxx"
			"x????"
			"x????",

			"x????"
			"xx"
			"xx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
			"xxxxx"
		);

		if ((pHudManagerInstance = bb_queue_pick_first(results))) {
			// pHudManagerInstance has been found
			DWORD addr;
			memcpy(&addr, pHudManagerInstance->data, sizeof(DWORD));
			addr = read_memory_as_int(mp->proc, addr);

			this->thisAddr = read_memory_as_int (mp->proc, addr);
			debug("HudManager pointer found : 0x%08X", this->thisAddr);

			// Get a copy of the structure in memory
			if (read_from_memory(mp->proc, this, this->thisAddr, sizeof(*this) - 4) != 0) {
				warning("(0x%.8x - 0x%.8x) RPM failed.", this->thisAddr);
			}

			// We don't need results anymore
			bb_queue_free_all (results, buffer_free);
		}
	}
}

void
HudManager_free (HudManager *HudManager)
{
	if (HudManager != NULL)
	{
		free (HudManager);
	}
}
