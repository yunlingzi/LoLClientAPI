// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "LoLProcess/LoLProcess.h"
#include "Keyboard/KeyState.h"

// ---------- Defines -------------
#define INVALID_OBJECT_HANDLE (-1)


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
 ** ====================================== Chat APIs ======================================
 ** ======================================================================================= **/

/*
 * Description : Get the next line of the chat received since the last time called.
 * Return : char * : A line of chat, or NULL if no message has been posted since the last time called.
 */
char *
get_chat_message (
	void
);

/*
 * Description : Log a message to the HudChat
 * char * message : A message to add in the chat
 * int messageLength : The length of the message, or -1 to calculate the length
 */
void
log_chat_message (
	char * message,
	int messageLength
);


/** =======================================================================================
 ** ==================================== Drawing APIs =====================================
 ** ======================================================================================= **/


/*
 * Description : Create a new rectangle displayed on the screen
 * int x, y                    : {x, y} position of the text
 * int w, h                    : width and height
 * byte r, byte g, byte b      : color of the rectangle
 * Return      : A unique ID handle of your rectangle object
 */
int
create_rectangle (
	int x, int y,
	int w, int h,
	byte r, byte g, byte b
);

/*
 * Description            : Create a new text displayed on the screen
 * char * string          : String of the text
 * int x, y               : {x, y} position of the text
 * byte r, byte g, byte b : color of the text
 * float opacity          : The opacity of the text.
 * int fontSize           : the size of the font
 * char * fontFamily      : The name of the family font. If NULL, "Arial" is used.
 * Return                 : A unique ID handle of your text object
 */
EXPORT_FUNCTION int
create_text (
	char * string,
	int x, int y,
	byte r, byte g, byte b,
	float opacity,
	int fontSize,
	char * fontFamily
);

/*
 * Description     : Create a new sprite displayed on the screen
 * char * filePath : Absolute or relative path of the image (.bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga)
 * int x, y        : {x, y} position of the image
 # float opacity   : opacity of the image, value between 0.0 and 1.0
 * Return          : A unique ID handle of your sprite object
 */
int
create_sprite (
	char *filePath,
	int x, int y,
	float opacity
);

/*
 * Description  : Change the position of the object on the screen.
 * int id       : The unique handle of the object to move
 # int x, int y : The new position on the screen of the object
 * Return       : void
 */
void
move_object (
	int id,
	int x, int y
);

/*
 * Description            : Change the attributes of the rectangle object.
 * int id                 : The unique handle of the object to modify
 * byte r, byte g, byte b : The new color of the next
 * int w, int h           : Width and height of the rectangle
 * Return                 : void
 */
void
rect_object_set (
	int id,
	byte r, byte g, byte b,
	int w, int h
);


/*
 * Description            : Change the attributes of the text object.
 * int id                 : The unique handle of the object to modify
 * char * string          : The new string of the text
 * byte r, byte g, byte b : The new color of the next
 * float opacity          : The new opacity of the text
 * Return                 : void
 */
void
text_object_set (
	int id,
	char * string,
	byte r, byte g, byte b,
	float opacity
);

/*
 * Description            : Change the attributes of the sprite object.
 * int id                 : The unique handle of the object to modify
 * float opacity          : The new opacity of the sprite
 * Return                 : void
 */
void
sprite_object_set (
	int id,
	float opacity
);

/*
 * Description : Show a hidden object. If it wasn't hidden, put it to the foreground of the screen.
 * int id      : The unique handle of the object to show
 * Return      : void
 */
void
show_object (
	int id
);

/*
 * Description : Show all hidden objects. Don't do anything with those already shown.
 * Return      : void
 */
void
show_all_objects (
	void
);

/*
 * Description : Hide a visible object.
				 It isn't deleted, so you can use show_object if you want to make it appear again.
 * int id      : The unique handle of the object to delete
 * Return      : void
 */
void
hide_object (
	int id
);


/*
 * Description : Show all hidden objects. Don't do anything with those already shown.
 * Return      : void
 */
void
hide_all_objects (
	void
);

/*
 * Description : Delete all the previously created objects on the screen
 * Return      : void
 */
void
delete_all_objects (
	void
);

/*
 * Description : Delete a specific object on the screen
 * int id      : The unique handle of the object to delete
 * Return      : void
 */
void
delete_object (
	int id
);

/*
 * Description : Return the object hovered by the mouse, or INVALID_OBJECT_HANDLE if no object is hovered
 * Return      : void
 */
int
get_hovered_object (
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
 * Description : Check if the API has retrieved the directx handle
 * Return      : true on success, false otherwise
 */
bool
check_directx (
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
 * Description : Wait for the DirectX handle to be in a ready state (blocking)
 */
void
wait_directx (
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

