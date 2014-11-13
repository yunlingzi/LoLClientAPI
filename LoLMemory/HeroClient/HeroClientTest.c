#include "HeroClient.h"
#include "LoLServerAPI/LoLServerInterface.h"

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
	if (this->pThis == 0) {
		warn ("HeroClient not detected. (Spectator mode ?)");
		return true;
	}

	/* Current position test */
	Position currentPosition;
	get_champion_position (&currentPosition.x, &currentPosition.y);

	if (!Position_in_map (&currentPosition)) {
		fail ("Current position test failed : %f %f", currentPosition.x, currentPosition.y);
	}

	/* Summoner name test */
	char * currentSummonerName = get_current_summoner_name ();
	for (int i = 0; i < sizeof_struct_member(HeroClient, summonerName); i++) {
		if (currentSummonerName[i] == 0) {
			break; // End of string reached
		}

		if (!(isalnum ((int) currentSummonerName[i]) || isspace((int) currentSummonerName[i]))) {
			fail ("Malformed summoner name : %s.", currentSummonerName);
		}
	}

	/* Hp test */
	float curHP, maxHP;
	get_champion_hp (&curHP, &maxHP);

	// 100000 HP seems to be big enough to be reported if the current/maximum HP is bigger
	if (curHP < 0.0 || maxHP < 0.0 || curHP > 100000.0 || maxHP > 100000.0) {
		fail ("HP test failed : cur=%f max=%f", this->curHP, this->maxHP);
	}

	/* Team test */
	if (get_champion_team () == TEAM_UNKNOWN) {
		fail ("Team test failed : 0x%x (%x)", this->team, &this->team);
	}

	return true;
}
