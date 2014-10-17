#include "HeroClient.h"
#include "LoLClientAPI.h"

#define __DEBUG_OBJECT__ "HeroClientTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a HeroClient is coherent
 * HeroClient *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HeroClient_test (
	HeroClient *this
) {
	Position currentPosition;
	get_champion_position (&currentPosition.x, &currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		dbg ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
		return false;
	}

	return true;
}
