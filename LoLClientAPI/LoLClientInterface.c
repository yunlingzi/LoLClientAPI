#include "LoLClientInterface.h"
#include "LoLAPI/LoLAPIPacket.h"
#include "LoLAPI/LoLAPIRequest.h"

#define __DEBUG_OBJECT__ "LoLClientInterface"
#include "dbg/dbg.h"

// Singleton
LoLClientAPI * api = NULL;

/** =================================================================================
 ** ================================== Camera APIs ==================================
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
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
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
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_POSITION,
		.gamePositionPacket.pos.x = x,
		.gamePositionPacket.pos.y = y
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
}


/*a
 * Description : Toggle built-in client camera movements
 *               For instance, camera movements when the cursor is on the border of the screen
 * __in__ bool enabled : If true, the camera client movements are enabled. False otherwise.
 * Return : void
 */
EXPORT_FUNCTION void
set_camera_client_enabled (
	__in__ bool enabled
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_CLIENT_ENABLED,
		.booleanPacket.value = enabled
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
}


/*
 * Description : Retrieve the current camera angle in degrees
 * __out__ float * angleX : A pointer to the X camera angle in degrees
 * __out__ float * angleY : A pointer to the Y camera angle in degrees
 */
EXPORT_FUNCTION void
get_camera_angle (
	__out__ float * angleX,
	__out__ float * angleY
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_ANGLE
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*angleX = packet.anglePacket.x;
		*angleY = packet.anglePacket.y;
	}
}


/*
 * Description : Set the current camera angle in degrees
 * __in__ float * angleX : A pointer to the X camera angle in degrees
 * __in__ float * angleY : A pointer to the Y camera angle in degrees
 */
EXPORT_FUNCTION void
set_camera_angle (
	__in__ float angleX,
	__in__ float angleY
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_ANGLE,
		.anglePacket.x = angleX,
		.anglePacket.y = angleY
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
}


/*
 * Description : Retrieve the current camera zoom value
 * Return : The zoom value
 */
EXPORT_FUNCTION float
get_camera_zoom (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_ZOOM
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));

	return packet.floatPacket.value;
}


/*
 * Description : Set the current camera zoom (1000.0 min, 2250.0 max)
 * __in__ float zoomValue : New zoom value
 */
EXPORT_FUNCTION void
set_camera_zoom (
	__in__ float zoomValue
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_ZOOM,
		.floatPacket.value = zoomValue
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
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
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURSOR_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
}


/*
 * Description : Retrieve the position of the cursor on the screen
 * __out__ int * x : A pointer to the X position
 * __out__ int * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_cursor_screen_position (
	__out__ int * x,
	__out__ int * y
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURSOR_SCREEN_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
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
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_DESTINATION_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
}


/*
 * Description : Check if the left mouse button is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_pressed (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_LEFT_MOUSE_BUTTON_PRESSED
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/*
 * Description : Check if the left mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_click (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_LEFT_MOUSE_BUTTON_CLICK
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/*
 * Description : Check if the right mouse button is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_pressed (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_RIGHT_MOUSE_BUTTON_PRESSED
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/*
 * Description : Check if the right mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_click (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_RIGHT_MOUSE_BUTTON_CLICK
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/** =======================================================================================
 ** =================================== Keyboard APIs =====================================
 ** ======================================================================================= **/


/*
 * Description : Check if the space key is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_space_pressed (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_SPACE_PRESSED
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/** =======================================================================================
 ** =================================== Champions APIs ====================================
 ** ======================================================================================= **/


// === Self champion ===

/*
 * Description : Retrieve the current champion position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_champion_position (
	__out__ float * x,
	__out__ float * y
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
}


/*
 * Description : Retrieve the current champion position
 * __out__ float * currentHP : A pointer to the current HP
 * __out__ float * maximumHP : A pointer to the maximum HP
 */
EXPORT_FUNCTION void
get_champion_hp (
	__out__ float * currentHP,
	__out__ float * maximumHP
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_HP
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*currentHP = packet.hpPacket.curHP;
		*maximumHP = packet.hpPacket.maxHP;
	}
}


/*
 * Description : Retrieve the current champion team
 * Return : 0 if BLUE team, 1 if PURPLE team
 */
EXPORT_FUNCTION int
get_champion_team (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_TEAM
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.intPacket.value;
	}

	return -1;
}

// === TeamMates ===

/*
 * Description : Retrieve the number of allies
 * Return : The number of allies in your team
 */
EXPORT_FUNCTION int
get_teammates_count (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATES_COUNT
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.intPacket.value;
	}

	return -1;
}


/*
 * Description : Check if the target teammate ID is valid
 * __in__  int teammateId : The target teammate ID
 * Return : true on success, false otherwise
 */
EXPORT_FUNCTION bool
check_teammate_id (
	__in__  int teammateId
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_CHECK_TEAMMATE_ID
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/*
 * Description : Retrieve the teammate champion position
 * __in__  int teammateId : The target teammate ID
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_teammate_position (
	__in__  int teammateId,
	__out__ float * x,
	__out__ float * y
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_POSITION,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.gamePositionPacket.pos.x;
		*y = packet.gamePositionPacket.pos.y;
	}
}


/*
 * Description : Retrieve teammate champion health points information
 * __in__  int teammateId : The target teammate ID
 * __out__ float * currentHP : A pointer to the current HP
 * __out__ float * maximumHP : A pointer to the maximum HP
 */
EXPORT_FUNCTION void
get_teammate_hp (
	__in__  int teammateId,
	__out__ float * currentHP,
	__out__ float * maximumHP
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_HP,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*currentHP = packet.hpPacket.curHP;
		*maximumHP = packet.hpPacket.maxHP;
	}
}


/*
 * Description : Retrieve teammate summoner name.
 * __in__  int teammateId : The target teammate ID
 * Return char * : A sequence of bytes containing the summoner name of the
 *                 target teammate (16 bytes maximum)
 */
EXPORT_FUNCTION char *
get_teammate_summoner_name (
	__in__  int teammateId
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_SUMMONER_NAME,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return strdup (packet.stringPacket.str);
	}

	return NULL;
}


/** =================================================================================
 ** ==================================== GUI APIs ===================================
 ** ================================================================================= **/

/*
 * Description : Retrieve the position of the minimap on the screen
 * __out__ int * x : A pointer to the X position
 * __out__ int * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_minimap_screen_position (
	__out__ int * x,
	__out__ int * y
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_MINIMAP_SCREEN_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		*x = packet.screenPositionPacket.x;
		*y = packet.screenPositionPacket.y;
	}
}


/*
 * Description : Check if the mouse is hovering the minimap
 * Return : bool True on success, false otherwise.
 */
EXPORT_FUNCTION bool
is_cursor_hovering_minimap (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_CURSOR_HOVERING_MINIMAP
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/** =======================================================================================
 ** ==================================== Summoner APIs ====================================
 ** ======================================================================================= **/


/*
 * Description : Retrieve the current summoner name
 * Return : char * The summoner name
 */
EXPORT_FUNCTION char *
get_current_summoner_name (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURRENT_SUMMONER_NAME
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return strdup (packet.stringPacket.str);
	}

	return NULL;
}


/** =================================================================================
 ** ================================= GameClock APIs ================================
 ** ================================================================================= **/


/*
 * Description : Get the current game time (as seconds)
 * Return : float the current time as seconds
 */
EXPORT_FUNCTION float
get_game_time (
	void
) {
	check_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_GAME_TIME
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))) {
		return packet.floatPacket.value;
	}

	return -1.0;
}



/** =================================================================================
 ** ================================== Internal APIs ================================
 ** ================================================================================= **/

/*
 * Description : Get the last error returned by the API.
 * Returns : An error code based on the last error received
 */
EXPORT_FUNCTION int
get_last_error (
	void
) {
	LoLClientAPIError lastError = api->lastError;
	api->lastError = API_NO_ERROR;
	return lastError;
}

/*
 * Description : Wait for the API to be in a ready state
 */
void
check_api (
	void
) {
	while (!(api != NULL && api->ready == true)) {
		Sleep (10);
	}
}

/*
 * Description : Set a new client api and initialize it to a ready state
 */
void
set_api_ready (
	LoLClientAPI * clientAPI
) {
	api = clientAPI;
	api->ready = true;
}
