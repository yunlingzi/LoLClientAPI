#include "HudCursorTarget.h"
#include "LoLClientAPI.h"

#define __DEBUG_OBJECT__ "HudCursorTargetTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a HudCursorTarget is coherent
 * HudCursorTarget *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudCursorTarget_test (
	HudCursorTarget *this
) {
	Position cursorPosition;
	get_camera_position (&cursorPosition.x, &cursorPosition.y);

	if (!Position_in_map (&cursorPosition)) {
		dbg ("Cursor position test failed : %f %f", cursorPosition.x, cursorPosition.y);
		return false;
	}

	return true;
}
