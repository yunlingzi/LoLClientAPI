#include "DestPos.h"
#include <stdlib.h>

#define __DEBUG_OBJECT__ "DestPos"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new DestPos structure.
 * MemProc *mp  : Address of an allocated and running MemProc target process
 * Return		: A pointer to an allocated DestPos.
 */
DestPos *
DestPos_new (
	MemProc *mp
) {
	DestPos *this;

	if ((this = calloc (1, sizeof(DestPos))) == NULL)
		return NULL;

	if (!DestPos_init (this, mp)) {
		DestPos_free (this);
		return NULL;
	}

	return this;
}


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
) {
	static char *description = "DestPos";

	BbQueue *results = memscan_search (mp, description,
		(unsigned char []) {
		// sub_B9A520
		/*     ║► └68 2C859C03     push offset League_of_Legends.039C852C        ; ╓Arg2 = League_of_Legends.39C852C
			   ║·  FF75 B8         push [dword ss:local.18]                      ; ║Arg1 => [LOCAL.18]
			   ║·  8BCF            mov ecx, edi                                  ; ║
			   ║·  E8 AF0D0000     call League_of_Legends.015080F0               ; └League_of_Legends.015080F0 */

			0x68, 0x2C, 0x85, 0x9C, 0x03,
			0xFF, 0x75,
			0xB8, 0x8B,
			0xCF, 0xE8, 0xAF, 0x0D, 0x00, 0x00

		},

		"x????"
		"xx"
		"xx"
		"xx????",

		"x????"
		"xx"
		"xx"
		"xxxxxx"
	);

	if (results)
	{
		DWORD pDest = *(DWORD *) ((Buffer *) bb_queue_pick_nth (results, 0))->data;
		this->pThis = read_memory_as_int (mp->proc, pDest);
		dbg ("DestPost found at 0x%08X.", this->pThis);

		return true;
	}

	return false;
}


/*
 * Description : Free an allocated DestPos structure.
 * DestPos *this : An allocated DestPos to free.
 */
void
DestPos_free (
	DestPos *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


