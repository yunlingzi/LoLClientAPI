#include "LoLProcess.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "LoLProcessTest"
#include "dbg/dbg.h"


/*
 * Description      : Unit tests checking if a LoLProcess is coherent
 * LoLProcess *this : The instance to test
 * Return           : true on success, false on failure
 */
bool
LoLProcess_test (
	LoLProcess *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	if (!LoLModule_test (this->lol)) {
		fail ("LoL module test fail.");
		return false;
	}

	return true;
}
