#include "DestPos.h"
#include "LoLClientAPI.h"

#define __DEBUG_OBJECT__ "DestPosTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a DestPos is coherent
 * DestPos *this : The instance to test
 * Return : true on success, false on failure
 */
bool
DestPos_test (
	DestPos *this
) {
	Position destPosition;
	get_cursor_position (&destPosition.x, &destPosition.y);

	if (!Position_in_map (&destPosition)) {
		dbg ("Destination position test failed : %f %f", destPosition.x, destPosition.y);
		return false;
	}

	return true;
}
