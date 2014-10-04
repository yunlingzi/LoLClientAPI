#include "LoLProcess.h"
#include <stdlib.h>


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
		return false;
	}

	return true;
}
