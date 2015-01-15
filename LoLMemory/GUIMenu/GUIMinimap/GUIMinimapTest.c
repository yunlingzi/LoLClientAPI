#include "GUIMinimap.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "GUIMinimapTest"
#include "dbg/dbg.h"


/*
 * Description      : Unit tests checking if a GUIMinimap is coherent
 * GUIMinimap *this : The instance to test
 * Return           : true on success, false on failure
 */
bool
GUIMinimap_test (
	GUIMinimap *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	Position2D screenPosition;

	if (!this->pThis) {
		fail ("GUIMinimap offset isn't correct.");
		return false;
	}

	get_minimap_screen_position (&screenPosition.x, &screenPosition.y);

	dbg ("Minimap screen position detected : x=%d y=%d", screenPosition.x, screenPosition.y);

	if (screenPosition.x == 0 && screenPosition.y == 0) {
		fail ("GUIMinimap position test failed.");
	}


	return true;
}

