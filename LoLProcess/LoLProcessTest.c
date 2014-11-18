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
		dbg ("HudManager test failed.");
		return false;
	}
	debug ("[OK] HudManager test success.");

	if (!HeroClient_test (this->heroClient)) {
		dbg ("HeroClient test failed.");
		return false;
	}
	debug ("[OK] HeroClient test success.");

	if (!ChampionArray_test (this->championArray)) {
		dbg ("ChampionArray test failed.");
		return false;
	}
	debug ("[OK] ChampionArray test success.");

	if (!GUIMenu_test (this->guiMenu)) {
		dbg ("GUIMenu unit test failed.");
		return false;
	}
	debug ("[OK] GUIMenu test success.");

	return true;
}
