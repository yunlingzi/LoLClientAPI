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
	if (!LoLModule_test (this->lol)) {
		dbg ("LoL module test fail.");
		return false;
	}

	return true;
}
