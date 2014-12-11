#include "Unit.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "UnitTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a Unit is coherent
 * Unit *this : The instance to test
 * Return : true on success, false on failure
 */
bool
Unit_test (
	Unit *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	/* Current position test */
	/*
	// TODO : Find a way to identify each Unit

	Position currentPosition;

	printf("this->teammateId = %d\n", this->teammateId);
	get_teammate_position (this->teammateId, &currentPosition.x, &currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		fail ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
	}

	// Unit name test
	char * currentSummonerName = get_current_summoner_name ();
	for (int i = 0; i < sizeof_struct_member(HeroClient, summonerName); i++) {
		if (currentSummonerName[i] == 0) {
			break; // End of string reached
		}

		if (!(isalnum ((int) currentSummonerName[i]) || isspace((int) currentSummonerName[i]))) {
			fail ("Malformed summoner name : %s.", currentSummonerName);
		}
	}
	*/

	return true;
}
