// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"

// ---------- Defines -------------


// ------ Structure declaration -------

typedef enum _LoLAPIRequest
{
	// Camera APIs
	REQUEST_GET_CAMERA_POSITION,
	REQUEST_SET_CAMERA_POSITION,
	REQUEST_SET_DEFAULT_CAMERA_ENABLED,
	REQUEST_GET_CAMERA_ANGLE,
	REQUEST_SET_CAMERA_ANGLE,
	REQUEST_GET_CAMERA_ZOOM,
	REQUEST_SET_CAMERA_ZOOM,

	// Cursor APIs
	REQUEST_GET_CURSOR_POSITION,
	REQUEST_GET_CURSOR_SCREEN_POSITION,
	REQUEST_GET_DESTINATION_POSITION,
	REQUEST_IS_LEFT_MOUSE_BUTTON_PRESSED,
	REQUEST_IS_LEFT_MOUSE_BUTTON_CLICK,
	REQUEST_IS_RIGHT_MOUSE_BUTTON_PRESSED,
	REQUEST_IS_RIGHT_MOUSE_BUTTON_CLICK,

	// Keyboard APIs
	REQUEST_IS_KEY_PRESSED,
	REQUEST_IS_KEY_TYPED,

	// Champion APIs
	REQUEST_GET_CHAMPION_POSITION,
	REQUEST_GET_CHAMPION_HP,
	REQUEST_GET_CHAMPION_TEAM,

	// Teammates APIs
	REQUEST_GET_TEAMMATES_COUNT,
	REQUEST_CHECK_TEAMMATE_ID,
	REQUEST_GET_TEAMMATE_POSITION,
	REQUEST_GET_TEAMMATE_HP,
	REQUEST_GET_TEAMMATE_SUMMONER_NAME,

	// Minimap APIs
	REQUEST_GET_MINIMAP_SCREEN_POSITION,
	REQUEST_IS_CURSOR_HOVERING_MINIMAP,

	// Summoner APIs
	REQUEST_GET_CURRENT_SUMMONER_NAME,

	// Game APIs
	REQUEST_GET_GAME_TIME,

	// Chat APIs
	REQUEST_GET_CHAT_MESSAGE,
	REQUEST_LOG_CHAT_MESSAGE,

	// Internal APIs
	REQUEST_EJECT_API,

	// Error status
	REQUEST_FAIL,
	REQUEST_UNDEFINED,

	REQUEST_API_COUNT

} 	LoLAPIRequest;


/*
 * Description : Convert a LoLAPIRequest to string
 * LoLAPIRequest request : The LoLApiRequest to convert
 * Return : char * the string
 */
char *
LoLAPIRequest_to_string (
	LoLAPIRequest request
);

/*
 * Description : Check if a LoLAPIRequest is valid
 * LoLAPIRequest *this : An allocated LoLAPIRequest
 * Return : bool true on success, false otherwise
 */
bool
LoLAPIRequest_is_valid (
	LoLAPIRequest request
);
