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
	/* Current position test */
	Position currentPosition;
	get_champion_position (&currentPosition.x, &currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		error ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
		return false;
	}

	/* Summoner name test */
	char * currentSummonerName = get_current_summoner_name ();

	for (int i = 0; i < sizeof_struct_member(HeroClient, summonerName); i++) {
		if (currentSummonerName[i] == 0) {
			break; // End of string reached
		}

		if (!(isalnum (currentSummonerName[i]) || isspace(currentSummonerName[i]))) {
			important ("Malformed summoner name : %s.", currentSummonerName);
		}
	}

	/* Hp test */
	float curHP, maxHP;
	get_champion_hp (&curHP, &maxHP);

	// 100000 HP seems to be big enough to be reported if the current/maximum HP is bigger
	if (curHP < 1.0 || maxHP < 1.0 || curHP > 100000.0 || maxHP > 100000.0) {
		important ("HP test failed : cur=%f max=%f", curHP, maxHP);
	}

	return true;
}
