#include "Unit.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "UnitTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a Unit is coherent
 * Unit *this  : The instance to test
 * Return      : true on success, false on failure
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
	Position currentPosition;

	if (this->teammateId < 0) {
		// Do not look into ennemies information
		return true;
	}

	get_teammate_position (this->teammateId, &currentPosition.x, &currentPosition.y);
	dbg ("Unit ally_%d position : %f %f", this->teammateId, currentPosition.x, currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		fail ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
	}

	// Unit name test
	char teammateSummonerName[17];

	get_teammate_summoner_name (this->teammateId, teammateSummonerName);
	for (int i = 0; i < sizeof_struct_member(HeroClient, summonerName); i++) {
		if (teammateSummonerName[i] == 0) {
			break; // End of string reached
		}

		if (!(isalnum ((int) teammateSummonerName[i]) || isspace((int) teammateSummonerName[i]))) {
			fail ("Malformed summoner name : %s.", teammateSummonerName);
		}
	}


	/* Hp test */
	float curHP, maxHP;
	get_teammate_hp (this->teammateId, &curHP, &maxHP);

	dbg ("Current HeroClient HP detected : %f/%f", curHP, maxHP);

	// 100000 HP seems to be big enough to be reported if the current/maximum HP is bigger
	if (curHP < 0.0 || maxHP < 0.0 || curHP > 100000.0 || maxHP > 100000.0) {
		fail ("HP test failed : cur=%f max=%f", this->curHP, this->maxHP);
	}

	return true;
}
