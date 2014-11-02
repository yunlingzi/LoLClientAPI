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

/*
 * Description : Toggle built-in client camera movements
 *               For instance, camera movements when the cursor is on the border of the screen
 * __in__ bool enabled : If true, the camera client movements are enabled
 * Return : void
 */
void
set_camera_client_enabled (
	__in__ bool enabled
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

/*
 * Description : Retrieve the position of the cursor on the screen
 * __out__ int * x : A pointer to the X position
 * __out__ int * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_cursor_screen_position (
	__out__ int * x,
	__out__ int * y
);

/*
 * Description : Retrieve the destination position (right click)
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_destination_position (
	__out__ float * x,
	__out__ float * y
);


/** =======================================================================================
 ** =================================== Champions APIs ====================================
 ** ======================================================================================= **/

// === Self champion ===

/*
 * Description : Retrieve the current champion position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
void
get_champion_position (
	__out__ float * x,
	__out__ float * y
);

/*
 * Description : Retrieve current champion health points information
 * __out__ float * currentHP : A pointer to the current HP
 * __out__ float * maximumHP : A pointer to the maximum HP
 */
void
get_champion_hp (
	__out__ float * currentHP,
	__out__ float * maximumHP
);

/*
 * Description : Retrieve the current champion team
 * Return : 0 if BLUE team, 1 if PURPLE team
 */
int
get_champion_team (
	void
);

// === TeamMates ===

/*
 * Description : Retrieve the number of allies
 * Return : The number of allies in your team
 */
int
get_teammates_count (
	void
);

/*
 * Description : Retrieve the teammate champion position
 * __in__  int allyId
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
void
get_teammate_position (
	__in__  int teammateId,
	__out__ float * x,
	__out__ float * y
);

/*
 * Description : Retrieve teammate champion health points information
 * __in__  int allyId
 * __out__ float * currentHP : A pointer to the current HP
 * __out__ float * maximumHP : A pointer to the maximum HP
 */
void
get_teammate_hp (
	__in__  int teammateId,
	__out__ float * currentHP,
	__out__ float * maximumHP
);

/*
 * Description : Retrieve teammate summoner name.
 * __in__  int teammateId : The target teammate ID
 * Return char * : A sequence of bytes containing the summoner name of the
 *                 target teammate (16 bytes maximum)
 */
char *
get_teammate_summoner_name (
	__in__  int teammateId
);

/*
 * Description : Check if the target teammate ID is valid. You shouldn't need to call this.
 * __in__  int teammateId : The target teammate ID
 * Return : true on success, false otherwise
 */
bool
check_teammate_id (
	__in__  int teammateId
);


/** =================================================================================
 ** ==================================== GUI APIs ===================================
 ** ================================================================================= **/

/*
 * Description : Retrieve the position of the minimap on the screen
 * __out__ int * x : A pointer to the X position
 * __out__ int * y : A pointer to the Y position
 */
void
get_minimap_screen_position (
	__out__ int * x,
	__out__ int * y
);


/*
 * Description : Check if the mouse is hovering the minimap
 * Return : bool True on success, false otherwise.
 */
bool
is_cursor_hovering_minimap (
	void
);


/** =======================================================================================
 ** ==================================== Summoner APIs ====================================
 ** ======================================================================================= **/

/*
 * Description : Retrieve the current summoner name
 * Return : char * The summoner name
 */
char *
get_current_summoner_name (
	void
);


/** =======================================================================================
 ** ================================== LoLClientAPI APIs ==================================
 ** ======================================================================================= **/

/*
 * Description : Check if the API has been correctly injected into LoL process
 * Return : true on successfully injected, false on failure
 */
bool
check_api (
	void
);

/*
 * Description : Wait for the API to be in ready state
 * Return : void
 */
void
waitForAPI (
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
