#include "GUIMenu.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "GUIMenuTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a GUIMenu is coherent
 * GUIMenu *this : The instance to test
 * Return : true on success, false on failure
 */
bool
GUIMenu_test (
	GUIMenu *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	if (!(GUIMinimap_test (this->guiMinimap))) {
		dbg ("GUIMinimap test unit failed.");
		return false;
	}
	dbg ("[OK] GUIMinimap test success.");

	return true;
}

