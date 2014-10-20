#include "ChampionArray.h"
#include "LoLClientAPI.h"

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
		important ("ChampionArray boundaries is egal to zero, test failed.");
		return false;
	}

	if (this->end < this->start) {
		important ("Wrong championArray boundaries, test failed.");
		return false;
	}

	if (this->championsCount > 12) {
		important ("The number of champions seems a bit weird : %d players.", this->championsCount);
	}

	for (int i = 0; i < this->championsCount; i++) {
		if (! Unit_test(this->champions[i])) {
			important ("Unit test Unit ID=%d failed.", i);
			return false;
		}
	}

	return true;
}
