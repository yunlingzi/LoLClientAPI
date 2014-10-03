#include "LolClientAPI.h"
#include "LoLProcess/LoLProcess.h"
#include <stdint.h>

#define _DEBUG_OBJECT__ "LoLClientAPI"

// LoLClientAPI singleton
LoLProcess * LoLClientAPI = NULL;


/**
 *	Description : Retrieve the current camera position
 *	__out__ float * x : A pointer to the X position
 *	__out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_camera_position (
	__out__ float * x,
	__out__ float * y
) {
	Position * cameraPosition = LoLProcess_get_addr (LoLClientAPI->hud, cameraPosition);

	*x = cameraPosition->x;
	*y = cameraPosition->y;
}


/**
 *	Description : Set the current camera position
 *	__in__ float x : New X position
 *	__in__ float y : New Y position
 */
EXPORT_FUNCTION void
set_camera_position (
	__in__ float x,
	__in__ float y
) {
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


