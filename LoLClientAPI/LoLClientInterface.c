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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_POSITION,
		.gamePositionPacket.pos.x = x,
		.gamePositionPacket.pos.y = y
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/*a
 * Description : Toggle the built-in client camera movements
 *               For instance, camera movements when the cursor is on the border of the screen
 * __in__ bool enabled : If true, the camera client movements are enabled. False otherwise.
 * Return : void
 */
EXPORT_FUNCTION void
set_default_camera_enabled (
	__in__ bool enabled
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_DEFAULT_CAMERA_ENABLED,
		.booleanPacket.value = enabled
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_ANGLE
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_ANGLE,
		.anglePacket.x = angleX,
		.anglePacket.y = angleY
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/*
 * Description : Retrieve the current camera zoom value
 * Return : The zoom value
 */
EXPORT_FUNCTION float
get_camera_zoom (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CAMERA_ZOOM
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));

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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SET_CAMERA_ZOOM,
		.floatPacket.value = zoomValue
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURSOR_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURSOR_SCREEN_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_DESTINATION_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_LEFT_MOUSE_BUTTON_PRESSED
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_LEFT_MOUSE_BUTTON_CLICK
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_RIGHT_MOUSE_BUTTON_PRESSED
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_RIGHT_MOUSE_BUTTON_CLICK
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}


/** =======================================================================================
 ** =================================== Keyboard APIs =====================================
 ** ======================================================================================= **/


/*
 * Description : Check if the given key is pressed
 * __in__ unsigned char key : ASCII code of the character pressed.
 *                            For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_pressed (
	__in__ unsigned char key
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_KEY_PRESSED,
		.bytePacket.value = key
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return packet.booleanPacket.value;
	}

	return false;
}



/*
 * Description : Check if the given key has been pressed and released
 * unsigned char key : ASCII code of the character typed.
 *                     For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns : true if typed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_typed (
	unsigned char key
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_KEY_TYPED,
		.bytePacket.value = key
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_HP
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAMPION_TEAM
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATES_COUNT
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_CHECK_TEAMMATE_ID
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_POSITION,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_HP,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_TEAMMATE_SUMMONER_NAME,
		.teammateId = teammateId
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return strdup (packet.bufferPacket.buffer);
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_MINIMAP_SCREEN_POSITION
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_IS_CURSOR_HOVERING_MINIMAP
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CURRENT_SUMMONER_NAME
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return strdup (packet.bufferPacket.buffer);
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
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_GAME_TIME
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return packet.floatPacket.value;
	}

	return -1.0;
}


/** =======================================================================================
 ** ====================================== Chat APIs ======================================
 ** ======================================================================================= **/

/*
 * Description : Get the next line of the chat received since the last time called.
 * Return : char * : A line of chat, or NULL if no message has been posted since the last time called.
 */
EXPORT_FUNCTION char *
get_chat_message (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_GET_CHAT_MESSAGE
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet)))
	{
		// Check if a new message has been received
		if (packet.objectPacket.size <= 0) {
			return NULL;
		}

		// The chat line is being sent as an dynamic object right after the first packet
		char *chatLine = calloc (1, packet.objectPacket.size + 1);
		if (!es_recv_buffer (api->clientSocket, chatLine, packet.objectPacket.size)) {
			warn ("Error when receiving the object packet (API_RECV_ERROR).");
			api->lastError = API_RECV_ERROR;
			return NULL;
		}

		return chatLine;
	}

	return NULL;
}


/*
 * Description : Log a message to the chat (only for you)
 * char * message : A line of chat to send
 * Return : void
 */
EXPORT_FUNCTION void
log_chat_message (
	char * message
) {
	wait_api ();

	int messageLength = strlen (message);

	LoLAPIPacket packet = {
		.request = REQUEST_LOG_CHAT_MESSAGE,
		.objectPacket.size = messageLength
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	es_send (api->clientSocket, message, messageLength);
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}

/** =======================================================================================
 ** ==================================== Drawing APIs =====================================
 ** ======================================================================================= **/

/*
 * Description            : Create a new colored rectangle displayed on the screen
 * int x, y               : {x, y} position of the text
 * int w, h               : width and height
 * byte r, byte g, byte b : color of the rectangle
 * Return                 : A unique handle of your rectangle object, or -1 if an error occurred
 */
EXPORT_FUNCTION int
create_rectangle (
	int x, int y,
	int w, int h,
	byte r, byte g, byte b
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_CREATE_RECTANGLE,
		.rectPacket.x = x,
		.rectPacket.y = y,
		.rectPacket.w = w,
		.rectPacket.h = h,
		.rectPacket.r = r,
		.rectPacket.g = g,
		.rectPacket.b = b
	};

	if (LoLClientAPI_send (api, &packet, sizeof(packet))
	 && LoLClientAPI_recv (api, &packet, sizeof(packet))) {
		return packet.intPacket.value;
	}

	return -1;
}

/*
 * Description : Show a hidden object. If it wasn't hidden, nothing happens.
 * int id      : The unique handle of the object to delete
 * Return      : void
 */
EXPORT_FUNCTION void
show_object (
	int id
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SHOW_OBJECT,
		.intPacket.value = id
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/*
 * Description : Show all hidden objects. Don't do anything with those already shown.
 * Return      : void
 */
EXPORT_FUNCTION void
show_all_objects (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_SHOW_ALL_OBJECTS
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/*
 * Description : Hide a visible object.
				 It isn't deleted, so you can use show_object if you want to make it appear again.
 * int id      : The unique handle of the object to delete
 * Return      : void
 */
EXPORT_FUNCTION void
hide_object (
	int id
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_HIDE_OBJECT,
		.intPacket.value = id
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/*
 * Description : Hide all hidden objects. Don't do anything with those already hidden.
 * Return      : void
 */
EXPORT_FUNCTION void
hide_all_objects (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_HIDE_ALL_OBJECTS
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}

/*
 * Description : Delete all the previously created objects on the screen
 * Return      : void
 */
EXPORT_FUNCTION void
delete_object (
	int id
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_DELETE_OBJECT,
		.intPacket.value = id
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}

/*
 * Description : Delete all the previously created objects on the screen
 * Return      : void
 */
EXPORT_FUNCTION void
delete_all_objects (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_DELETE_ALL_OBJECTS
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));
}


/** =================================================================================
 ** ================================== Internal APIs ================================
 ** ================================================================================= **/

/*
 * Description : Eject the API from the LoL process
 */
EXPORT_FUNCTION bool
eject_api (
	void
) {
	wait_api ();

	LoLAPIPacket packet = {
		.request = REQUEST_EJECT_API
	};

	LoLClientAPI_send (api, &packet, sizeof(packet));
	LoLClientAPI_recv (api, &packet, sizeof(packet));

	// Check exit status
	if (strcmp (packet.bufferPacket.buffer, LOLAPI_STATUS_EXIT) != 0) {
		warn ("Malformed LoLAPIServer exit status response.");
		return false;
	}

	// Sleep a bit so we let time for the server to exit gracefully
	Sleep (1000);
	return true;
}


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
 * Description : Check if the API has been correctly injected into LoL process
 * Return : true on successfully injected, false on failure
 */
EXPORT_FUNCTION bool
check_api (
	void
) {
	return (api != NULL && api->ready == true);
}

/*
 * Description : Wait for the API to be in a ready state (blocking)
 */
EXPORT_FUNCTION void
wait_api (
	void
) {
	while (!check_api ()) {
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
