#include "ChampionArray.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "ChampionArrayTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a ChampionArray is coherent
 * ChampionArray *this : The instance to test
 * Return : true on success, false on failure
 */
bool
ChampionArray_test (
	ChampionArray *this
) {
	if (this->end == 0 || this->start == 0) {
		fail ("ChampionArray boundaries is egal to zero, test failed.");
		return false;
	}

	if (this->end < this->start) {
		fail ("Wrong championArray boundaries, test failed.");
		return false;
	}

	if (this->championsCount > 12) {
		fail ("The number of champions seems a bit weird : %d players.", this->championsCount);
	}

	for (int i = 0; i < this->championsCount; i++) {
		dbg ("Testing %.16s ...", this->champions[i]->summonerName);

		if (! Unit_test (this->champions[i])) {
			fail ("Unit test Unit ID=%d failed.", i);
			return false;
		}
	}

	return true;
}
