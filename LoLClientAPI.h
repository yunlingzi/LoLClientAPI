#pragma once

#define __out__
#define __in__
#define __opt__
#define __inout__

// Debug
#define __DBG_ACTIVATED__ TRUE

// Dependencies
#include "LoLProcess/LoLProcess.h"



/** =================================================================================
 ** ================================== CAMERA APIs ==================================
 ** ================================================================================= **/

/*
 *	Description : Retrieve the current camera position
 *	__out__ float * x : A pointer to the X position
 *	__out__ float * y : A pointer to the Y position
 */
void
get_camera_position (
	__out__ float * x,
	__out__ float * y
);

/*
 *	Description : Set the current camera position
 *	__in__ float x : New X position
 *	__in__ float y : New Y position
 */
void
set_camera_position (
	__in__ float x,
	__in__ float y
);


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
);


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
);

/*
 * Description : Set the current used LoLClientAPI instance
 * __in__ LoLProcess *instance : Set the global LoLClientAPI value to this argument
 * Note : /!\ Use it only if you know what you are doing !
 */
void
set_LoLClientAPI (
	__in__ LoLProcess *instance
);

/*
 * Description : Get the current used LoLClientAPI instance
 * Return LoLProcess * : A pointer to the current LoLClientAPI instance
 * Note : /!\ Use it only if you know what you are doing !
 */
LoLProcess *
get_LoLClientAPI (
	void
);
