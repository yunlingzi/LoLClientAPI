#include "HudCamera.h"
#include "LoLClientAPI.h"

#define __DEBUG_OBJECT__ "HudCameraTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a HudCamera is coherent
 * HudCamera *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudCamera_test (
	HudCamera *this
) {
	Position cameraPosition;
	get_camera_position (&cameraPosition.x, &cameraPosition.y);

	if (!Position_in_map (&cameraPosition)) {
		important ("Camera position test failed : %f %f", cameraPosition.x, cameraPosition.y);
	}

	return true;
}

