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
	waitForAPI ();

	HudCamera * hudCamera      = LoLClientAPI->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

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
	waitForAPI ();

	HudCamera * hudCamera      = LoLClientAPI->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

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
	waitForAPI ();

	HudCursorTarget * hudCursorTarget = LoLClientAPI->hudManager->hudCursorTarget;
	Position        * cursorPosition  = LoLProcess_get_addr (hudCursorTarget, posRaw);

	*x = cursorPosition->x;
	*y = cursorPosition->y;
}


/*
 * Description : Retrieve the destination position (right click)
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_destination_position (
	__out__ float * x,
	__out__ float * y
) {
	waitForAPI ();

	HudCursorTarget * hudCursorTarget = LoLClientAPI->hudManager->hudCursorTarget;
	Position * rightClickPosition = LoLProcess_get_addr (hudCursorTarget, rightClickPosition);

	*x = rightClickPosition->x;
	*y = rightClickPosition->y;
}


/** =======================================================================================
 ** =================================== Champions APIs ====================================
 ** ======================================================================================= **/

/*
 * Description : Retrieve the current champion position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
void
get_champion_position (
	__out__ float * x,
	__out__ float * y
) {
	waitForAPI ();

	HeroClient * currentChampion = LoLClientAPI->heroClient;
	Position * currentChampionPosition = LoLProcess_get_addr (currentChampion, currentPosition);

	*x = currentChampionPosition->x;
	*y = currentChampionPosition->y;
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
	return (
		(LoLClientAPI != NULL)
	&&  (LoLClientAPI->state == STATE_READY));
}


/*
 * Description : Wait for the API to be in ready state
 * Return : void
 */
EXPORT_FUNCTION void
waitForAPI (
	void
) {
	while (!check_api ()) {
		dbg ("LoLClientAPI is injecting LoLProcess. Please wait...");
		Sleep (1000);
	}
}


/*
 * Description : Set the current used LoLClientAPI instance
 * __in__ LoLProcess *instance : Set the global LoLClientAPI value to this argument
 * Note : /!\ Use it only if you know what you are doing !
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
 * Note : /!\ Use it only if you know what you are doing !
 */
EXPORT_FUNCTION LoLProcess *
get_LoLClientAPI (
	void
) {
	return LoLClientAPI;
}
