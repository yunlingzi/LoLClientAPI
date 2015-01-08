#include "HudCursorTarget.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "HudCursorTargetTest"
#include "dbg/dbg.h"


/*
 * Description           : Unit tests checking if a HudCursorTarget is coherent
 * HudCursorTarget *this : The instance to test
 * Return                : true on success, false on failure
 */
bool
HudCursorTarget_test (
	HudCursorTarget *this
) {
	Position cursorPosition;
	get_cursor_position (&cursorPosition.x, &cursorPosition.y);

	if (!Position_in_map (&cursorPosition)) {
		fail ("Cursor position test failed : %f %f", cursorPosition.x, cursorPosition.y);
	}

	return true;
}
