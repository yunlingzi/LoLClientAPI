#include "Unit.h"
#include "LoLClientAPI.h"

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
	/* Current position test */
	// Position currentPosition;

	// TODO : Find a way to identify each Unit

	/*
	get_champion_position (&currentPosition.x, &currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		important ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
	}
	*/

	/* Unit name test */
	/*
	char * currentSummonerName = get_current_summoner_name ();
	for (int i = 0; i < sizeof_struct_member(HeroClient, summonerName); i++) {
		if (currentSummonerName[i] == 0) {
			break; // End of string reached
		}

		if (!(isalnum ((int) currentSummonerName[i]) || isspace((int) currentSummonerName[i]))) {
			important ("Malformed summoner name : %s.", currentSummonerName);
		}
	}
	*/

	return true;
}
