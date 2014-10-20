#include "Unit.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "Unit"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new Unit structure.
 * MemProc *mp  : Handle to the target process
 * DWORD pUnit : The address of the Unit in the target process
 * Return		: A pointer to an allocated Unit.
 */
Unit *
Unit_new (
	MemProc *mp,
	DWORD pUnit
) {
	Unit *this;

	if ((this = calloc (1, sizeof(Unit))) == NULL)
		return NULL;

	if (!Unit_init (this, mp, pUnit)) {
		Unit_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated Unit structure.
 * MemProc *mp  : Handle to the target process
 * Unit *this : An allocated Unit to initialize.
 * DWORD pUnit : The address of the Unit in the target process
 * Return : true on success, false on failure.
 */
bool
Unit_init (
	Unit *this,
	MemProc *mp,
	DWORD pUnit
) {
	read_from_memory (mp->proc, this, pUnit, sizeof(Unit));

	this->pThis = pUnit;

	dbg ("Unit <%s> detected. (0x%08X)", this->summonerName, pUnit);

	return true;
}


/*
 * Description : Free an allocated Unit structure.
 * Unit *this : An allocated Unit to free.
 */
void
Unit_free (
	Unit *this
) {
	if (this != NULL)
	{
		free (this);
	}
}
