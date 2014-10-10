#include "HudManager.h"
#include "LoLClientAPI.h"

#define __DEBUG_OBJECT__ "HudManagerTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a HudManager is coherent
 * HudManager *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudManager_test (
	HudManager *this
) {
	if (!HudCamera_test (this->hudCamera)) {
		dbg ("HudCamera unit test failed.");
		return false;
	}

	if (!HudCursorTarget_test (this->hudCursorTarget)) {
		dbg ("hudCursorTarget unit test failed.");
		return false;
	}

	return true;
}
