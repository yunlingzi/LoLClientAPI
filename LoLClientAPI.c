#include "LolClientAPI.h"
#include "LoLProcess/LoLProcess.h"
#include <stdint.h>

#define __DEBUG_OBJECT__ "LoLClientAPI"
#include "dbg/dbg.h"


// LoLClientAPI singleton
LoLProcess * LoLClientAPI = NULL;


/** =================================================================================
 ** ================================== CAMERA APIs ==================================
 ** ================================================================================= **/

/*
 * Description : Retrieve the current camera position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_camera_position (
	__out__ float * x,
	__out__ float * y
) {
	if (!check_api ()) {
		dbg ("LoLClientAPI is not installed correctly.");
		return;
	}

	HudCamera * hudCamera = LoLClientAPI->hudManager->hudCamera;
	Position * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	printf("%x\n", LoLProcess_get_remote_addr (hudCamera, cameraPosition));
	*x = cameraPosition->x;
	*y = cameraPosition->y;
}


/*
 * Description : Set the current camera position
 * __in__ float x : New X position
 * __in__ float y : New Y position
 */
EXPORT_FUNCTION void
set_camera_position (
	__in__ float x,
	__in__ float y
) {
	if (!check_api ()) {
		dbg ("LoLClientAPI is not installed correctly.");
		return;
	}

	HudCamera * hudCamera = LoLClientAPI->hudManager->hudCamera;
	Position * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	cameraPosition->x = x;
	cameraPosition->y = y;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			LoLClientAPI->process->proc,
			LoLProcess_get_remote_addr (hudCamera, cameraPosition),
			cameraPosition,
			sizeof(*cameraPosition),
			NULL
		);
	#endif
}

/** =================================================================================
 ** ================================== Cursor APIs ==================================
 ** ================================================================================= **/

/*
 * Description : Retrieve the current cursor position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_cursor_position (
	__out__ float * x,
	__out__ float * y
) {
	if (!check_api ()) {
		dbg ("LoLClientAPI is not installed correctly.");
		return;
	}

	HudCursorTarget * hudCursorTarget = LoLClientAPI->hudManager->hudCursorTarget;
	Position * cursorPosition = LoLProcess_get_addr (hudCursorTarget, posRaw);

	printf("hudCursorTarget->posRaw = %x\n", LoLProcess_get_remote_addr (hudCursorTarget, posRaw));
	*x = cursorPosition->x;
	*y = cursorPosition->y;
}



/** =======================================================================================
 ** ================================== LoLClientAPI APIs ==================================
 ** ======================================================================================= **/

/*
 * Description : Check if the API has been correctly injected into LoL process
 * Return : true on successfully injected, false on failure
 */
EXPORT_FUNCTION bool
check_api (
	void
) {
	return (LoLClientAPI != NULL);
}


/*
 * Description : Set the current used LoLClientAPI instance
 * __in__ LoLProcess *instance : Set the global LoLClientAPI value to this argument
 */
EXPORT_FUNCTION void
set_LoLClientAPI (
	__in__ LoLProcess *instance
) {
	LoLClientAPI = instance;
}


/*
 * Description : Get the current used LoLClientAPI instance
 * Return LoLProcess * : A pointer to the current LoLClientAPI instance
 */
EXPORT_FUNCTION LoLProcess *
get_LoLClientAPI (
	void
) {
	return LoLClientAPI;
}
