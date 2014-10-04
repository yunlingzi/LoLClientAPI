#include "LolClientAPI.h"
#include "LoLProcess/LoLProcess.h"
#include <stdint.h>

#define _DEBUG_OBJECT__ "LoLClientAPI"


// LoLClientAPI singleton
LoLProcess * LoLClientAPI = NULL;


/**
 * Description : Check if the API has been correctly injected into LoL process
 * Return : true on success, false on failure
 */
EXPORT_FUNCTION bool
check_api (
	void
) {
	return (LoLClientAPI == NULL);
}


/**
 * Description : Retrieve the current camera position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_camera_position (
	__out__ float * x,
	__out__ float * y
) {
	check_api ();

	Position * cameraPosition = LoLProcess_get_addr (LoLClientAPI->hud, cameraPosition);

	*x = cameraPosition->x;
	*y = cameraPosition->y;
}


/**
 * Description : Set the current camera position
 * __in__ float x : New X position
 * __in__ float y : New Y position
 */
EXPORT_FUNCTION void
set_camera_position (
	__in__ float x,
	__in__ float y
) {
	check_api ();

	Position * cameraPosition = LoLProcess_get_addr (LoLClientAPI->hud, cameraPosition);

	cameraPosition->x = x;
	cameraPosition->y = y;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			LoLClientAPI->process->proc,
			LoLProcess_get_remote_addr (LoLClientAPI->hud, cameraPosition),
			cameraPosition,
			sizeof(*cameraPosition),
			NULL
		);
	#endif
}


/**
 * Description : Set the current used LoLClientAPI instance
 * __in__ LoLProcess *instance : Set the global LoLClientAPI value to this argument
 */
EXPORT_FUNCTION void
set_LoLClientAPI (
	__in__ LoLProcess *instance
) {
	LoLClientAPI = instance;
}


/**
 * Description : Get the current used LoLClientAPI instance
 * Return LoLProcess * : A pointer to the current LoLClientAPI instance
 */
EXPORT_FUNCTION LoLProcess *
get_LoLClientAPI (
	void
) {
	return LoLClientAPI;
}
