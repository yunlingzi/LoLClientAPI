#include "HudManager.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "HudManagerTest"
#include "dbg/dbg.h"


/*
 * Description      : Unit tests checking if a HudManager is coherent
 * HudManager *this : The instance to test
 * Return           : true on success, false on failure
 */
bool
HudManager_test (
	HudManager *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	if (!HudCamera_test (this->hudCamera)) {
		fail ("HudCamera unit test failed.");
		return false;
	}
	dbg ("[OK] HudCamera test success.");

	if (!HudCameraSettings_test (this->hudCameraSettings)) {
		fail ("HudCameraSettings unit test failed.");
		return false;
	}
	dbg ("[OK] HudCameraSettings test success.");

	if (!HudCursorTarget_test (this->hudCursorTarget)) {
		fail ("HudCursorTarget unit test failed.");
		return false;
	}
	dbg ("[OK] HudCursorTarget test success.");

	return true;
}
