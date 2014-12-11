// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "LoLProcess/LoLProcess.h"
#include "Keyboard/KeyState.h"

// ---------- Defines -------------



/** =================================================================================
 ** ================================== Camera APIs ==================================
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
 * Description : Toggle the built-in client default camera movements
 *               For instance, camera movements when the cursor is on the border of the screen
 * __in__ bool enabled : If true, the camera client movements are enabled
 * Return : void
 */
void
set_default_camera_enabled (
	__in__ bool enabled
);

/*
 * Description : Retrieve the current camera angle in degrees
 * __out__ float * angleX : A pointer to the X camera angle in degrees
 * __out__ float * angleY : A pointer to the Y camera angle in degrees
 */
void
get_camera_angle (
	__out__ float * angleX,
	__out__ float * angleY
);

/*
 * Description : Set the current camera angle in degrees
 * __in__ float * angleX : A pointer to the X camera angle in degrees
 * __in__ float * angleY : A pointer to the Y camera angle in degrees
 */
void
set_camera_angle (
	__in__ float angleX,
	__in__ float angleY
);

/*
 * Description : Retrieve the current camera zoom value
 * Return : Zoom value
 */
float
get_camera_zoom (
	void
);

/*
 * Description : Set the current camera zoom (500.0 min, 2000.0 max)
 * __in__ float zoomValue : New zoom value
 */
void
set_camera_zoom (
	__in__ float zoomValue
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

/*
 * Description : Check if the left mouse button is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_pressed (
	void
);

/*
 * Description : Check if the left mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_click (
	void
);

/*
 * Description : Check if the right mouse button is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_pressed (
	void
);

/*
 * Description : Check if the right mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_click (
	void
);


/** =======================================================================================
 ** =================================== Keyboard APIs =====================================
 ** ======================================================================================= **/

/*
 * Description : Check if the given key is pressed
 * unsigned char key : ASCII code of the character pressed.
 *                     For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_typed (
	unsigned char key
);


/*
 * Description : Check if the given key is pressed
 * unsigned char key : ASCII code of the character pressed.
 *                     For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_pressed (
	unsigned char key
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
 * __in__ char * summonerName : A sequence of bytes containing the summoner name of the
 *                              target teammate (16 bytes maximum)
 */
void
get_teammate_summoner_name (
	__in__  int teammateId,
	__in__ char * summonerName
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
 * __in__ char * summonerName : A sequence of bytes containing the summoner name of the
 *                              target teammate (16 bytes maximum)
 */
void
get_current_summoner_name (
	__in__ char * summonerName
);


/** =================================================================================
 ** ================================= GameClock APIs ================================
 ** ================================================================================= **/

/*
 * Description : Get the current game time (as seconds)
 * Return : float the current time as seconds
 */
float
get_game_time (
	void
);


/** =======================================================================================
 ** ================================== LoLServerAPI APIs ==================================
 ** ======================================================================================= **/

/*
 * Description : Check if the API has been correctly injected into LoL process (nonblocking)
 * Return : true on successfully injected, false on failure
 */
bool
check_api (
	void
);

/*
 * Description : Wait for the API to be in a ready state (blocking)
 */
void
wait_api (
	void
);


/*
 * Description : Set the current used LoLServerAPI instance
 * __in__ LoLProcess *instance : Set the global LoLServerAPI value to this argument (not exported in the DLL)
 */
void
set_LoLProcess (
	__in__ LoLProcess *instance
);

/*
 * Description : Get the current used LoLServerAPI instance
 * Return LoLProcess * : A pointer to the current LoLServerAPI instance (not exported in the DLL)
 */
LoLProcess *
get_LoLProcess (
	void
);


