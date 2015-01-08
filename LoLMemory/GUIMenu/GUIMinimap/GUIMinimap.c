#include "GUIMinimap.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "GUIMinimap"
#include "dbg/dbg.h"

/*
 * Description 	     : Allocate a new GUIMinimap structure.
 * DWORD pGuiMinimap : Address of the GUIMinimap in the target process
 * Return		          : A pointer to an allocated GUIMinimap.
 */
GUIMinimap *
GUIMinimap_new (
	DWORD pGuiMinimap
) {
	GUIMinimap *this;

	if ((this = calloc (1, sizeof(GUIMinimap))) == NULL)
		return NULL;

	if (!GUIMinimap_init (this, pGuiMinimap)) {
		GUIMinimap_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description       : Initialize an allocated GUIMinimap structure.
 * GUIMinimap *this  : An allocated GUIMinimap to initialize.
 * DWORD pGuiMinimap : Address of the GUIMinimap in the target process
 */
bool
GUIMinimap_init (
	GUIMinimap *this,
	DWORD pGuiMinimap
) {
	this->pThis = pGuiMinimap;

	return true;
}


/*
 * Description       : Free an allocated GUIMinimap structure.
 * GUIMinimap *this  : An allocated GUIMinimap to free.
 */
void
GUIMinimap_free (
	GUIMinimap *this
) {
	if (this != NULL)
	{
		free (this);
	}
}

