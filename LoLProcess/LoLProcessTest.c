#include "LoLProcess.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "LolProcessTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a LoLProcess is coherent
 * LoLProcess *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLProcess_test (
	LoLProcess *this
) {
	if (!HudManager_test (this->hudManager)) {
		dbg ("HudManager unit test failed.");
		return false;
	}

	if (!HeroClient_test (this->heroClient)) {
		dbg ("HeroClient unit test failed.");
		return false;
	}

	if (!ChampionArray_test (this->championArray)) {
		dbg ("ChampionArray unit test failed.");
		return false;
	}

	if (!GUIMenu_test (this->guiMenu)) {
		dbg ("GUIMenu unit test failed.");
		return false;
	}

	return true;
}
