#include "LoLServerAPI/LoLServerInterface.h"
#include "LoLProcess/LoLProcess.h"
#include "Keyboard/Keyboard.h"
#include "D3D9Hook/D3D9Object.h"
#include <stdint.h>

#define __DEBUG_OBJECT__ "LoLServerInterface"
#include "dbg/dbg.h"


// Singleton containing all the client information
LoLProcess * lolClient = NULL;


/** =================================================================================
 ** ================================== Camera APIs ==================================
 ** ================================================================================= **/


/*
 * Description            : Retrieve the current camera position
 * __out__ float * x      : A pointer to the X position
 * __out__ float * y      : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_camera_position (
	__out__ float * x,
	__out__ float * y
) {
	wait_api ();

	HudCamera * hudCamera      = lolClient->lol->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	*x = cameraPosition->x;
	*y = cameraPosition->y;
}


/*
 * Description     : Set the current camera position
 * __in__ float x  : New X position
 * __in__ float y  : New Y position
 */
EXPORT_FUNCTION void
set_camera_position (
	__in__ float x,
	__in__ float y
) {
	wait_api ();

	HudCamera * hudCamera      = lolClient->lol->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	cameraPosition->x = x;
	cameraPosition->y = y;
}


/*a
 * Description            : Toggle the built-in client default camera movements
 *                          For instance, camera movements when the cursor is on the border of the screen
 * __in__ bool enabled    : If true, the camera client movements are enabled. False otherwise.
 * Return                 : void
 */
EXPORT_FUNCTION void
set_default_camera_enabled (
	__in__ bool enabled
) {
	wait_api ();

	HudCameraSettings * hudCameraSettings = lolClient->lol->hudManager->hudCameraSettings;
	int * cameraActivated = LoLProcess_get_addr (hudCameraSettings, cameraActivated);

	*cameraActivated = enabled;
}


/*
 * Description            : Retrieve the current camera angle in degrees
 * __out__ float * angleX : A pointer to the X camera angle in degrees
 * __out__ float * angleY : A pointer to the Y camera angle in degrees
 */
EXPORT_FUNCTION void
get_camera_angle (
	__out__ float * angleX,
	__out__ float * angleY
) {
	wait_api ();

	HudCamera * hudCamera = lolClient->lol->hudManager->hudCamera;
	HudCameraAngle * hudCameraAngle = LoLProcess_get_addr (hudCamera, cameraAngle);

	*angleX = hudCameraAngle->x;
	*angleY = hudCameraAngle->y;
}


/*
 * Description            : Set the current camera angle in degrees
 * __in__ float * angleX  : A pointer to the X camera angle in degrees
 * __in__ float * angleY  : A pointer to the Y camera angle in degrees
 */
EXPORT_FUNCTION void
set_camera_angle (
	__in__ float angleX,
	__in__ float angleY
) {
	wait_api ();

	HudCamera * hudCamera = lolClient->lol->hudManager->hudCamera;
	HudCameraAngle * cameraAngle = LoLProcess_get_addr (hudCamera, cameraAngle);

	cameraAngle->x = angleX;
	cameraAngle->y = angleY;
}


/*
 * Description  : Retrieve the current camera zoom value
 * Return       : The zoom value
 */
EXPORT_FUNCTION float
get_camera_zoom (
	void
) {
	wait_api ();

	HudCamera * hudCamera = lolClient->lol->hudManager->hudCamera;
	HudCameraZoom * cameraZoom = LoLProcess_get_addr (hudCamera, cameraZoom);

	return cameraZoom->curValue;
}


/*
 * Description            : Set the current camera zoom (1000.0 min, 2250.0 max)
 * __in__ float zoomValue : New zoom value
 */
EXPORT_FUNCTION void
set_camera_zoom (
	__in__ float zoomValue
) {
	wait_api ();

	HudCamera * hudCamera = lolClient->lol->hudManager->hudCamera;
	HudCameraZoom * cameraZoom = LoLProcess_get_addr (hudCamera, cameraZoom);

	cameraZoom->targetValue = zoomValue;
}


/** =================================================================================
 ** ================================== Cursor APIs ==================================
 ** ================================================================================= **/


/*
 * Description       : Retrieve the current cursor position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_cursor_position (
	__out__ float * x,
	__out__ float * y
) {
	wait_api ();

	HudCursorTarget * hudCursorTarget = lolClient->lol->hudManager->hudCursorTarget;
	Position        * cursorPosition  = LoLProcess_get_addr (hudCursorTarget, posRaw);

	*x = cursorPosition->x;
	*y = cursorPosition->y;
}


/*
 * Description      : Retrieve the position of the cursor on the screen
 * __out__ int * x  : A pointer to the X position
 * __out__ int * y  : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_cursor_screen_position (
	__out__ int * x,
	__out__ int * y
) {
	POINT point;
	GetCursorPos (&point);

	*x = point.x;
	*y = point.y;
}


/*
 * Description       : Retrieve the destination position (right click)
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_destination_position (
	__out__ float * x,
	__out__ float * y
) {
	wait_api ();

	HudCursorTarget * hudCursorTarget = lolClient->lol->hudManager->hudCursorTarget;
	Position * rightClickPosition = LoLProcess_get_addr (hudCursorTarget, rightClickPosition);

	*x = rightClickPosition->x;
	*y = rightClickPosition->y;
}


/*
 * Description : Check if the left mouse button is pressed
 * Returns     : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_pressed (
	void
) {
	return is_key_pressed (VK_LBUTTON);
}


/*
 * Description : Check if the left mouse button is clicked
 * Returns     : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_click (
	void
) {
	// Works similarly than keyboard keys
	return is_key_typed (VK_LBUTTON);
}


/*
 * Description : Check if the right mouse button is pressed
 * Returns     : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_pressed (
	void
) {
	return is_key_pressed (VK_RBUTTON);
}


/*
 * Description : Check if the right mouse button is clicked
 * Returns     : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_click (
	void
) {
	// Works similarly than keyboard keys
	return is_key_typed (VK_RBUTTON);
}


/** =======================================================================================
 ** =================================== Keyboard APIs =====================================
 ** ======================================================================================= **/

/*
 * Description       : Check if the given key has been pressed and released
 * unsigned char key : ASCII code of the character typed.
 *                     For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns           : true if typed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_typed (
	unsigned char key
) {
	return Keyboard_is_key_typed (key);
}

/*
 * Description       : Check if the given key is pressed
 * unsigned char key : ASCII code of the character pressed.
 *                     For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
 * Returns           : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_key_pressed (
	unsigned char key
) {
	return Keyboard_is_key_pressed (key);
}


/** =======================================================================================
 ** =================================== Champions APIs ====================================
 ** ======================================================================================= **/


// === Self champion ===

/*
 * Description       : Retrieve the current champion position
 * __out__ float * x : A pointer to the X position
 * __out__ float * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_champion_position (
	__out__ float * x,
	__out__ float * y
) {
	wait_api ();

	HeroClient * currentChampion = lolClient->lol->heroClient;
	Position   * currentChampionPosition = LoLProcess_get_addr (currentChampion, currentPosition);

	*x = currentChampionPosition->x;
	*y = currentChampionPosition->y;
}


/*
 * Description               : Retrieve the current champion position
 * __out__ float * currentHP : A pointer to the current HP
 * __out__ float * maximumHP : A pointer to the maximum HP
 */
EXPORT_FUNCTION void
get_champion_hp (
	__out__ float * currentHP,
	__out__ float * maximumHP
) {
	wait_api ();

	HeroClient * currentChampion = lolClient->lol->heroClient;
	float *currentChampionCurrentHP = (float *) LoLProcess_get_addr (currentChampion, curHP);
	float *currentChampionMaximumHP = (float *) LoLProcess_get_addr (currentChampion, maxHP);

	*currentHP = *currentChampionCurrentHP;
	*maximumHP = *currentChampionMaximumHP;
}


/*
 * Description : Retrieve the current champion team
 * Return      : TEAM_BLUE, TEAM_PURPLE or TEAM_UNKNOWN
 */
EXPORT_FUNCTION int
get_champion_team (
	void
) {
	wait_api ();

	HeroClient * currentChampion = lolClient->lol->heroClient;
	int *currentChampionTeam = LoLProcess_get_addr (currentChampion, team);

	if (*currentChampionTeam == CLIENT_TEAM_BLUE) {
		return TEAM_BLUE;
	}

	if (*currentChampionTeam == CLIENT_TEAM_PURPLE) {
		return TEAM_PURPLE;
	}

	return TEAM_UNKNOWN;
}

// === TeamMates ===

/*
 * Description : Retrieve the number of allies
 * Return      : The number of allies in your team
 */
EXPORT_FUNCTION int
get_teammates_count (
	void
) {
	wait_api ();

	ChampionArray * champArray = lolClient->lol->championArray;

	return champArray->teammatesCount;
}


/*
 * Description            : Check if the target teammate ID is valid
 * __in__  int teammateId : The target teammate ID
 * Return                 : true on success, false otherwise
 */
EXPORT_FUNCTION bool
check_teammate_id (
	__in__  int teammateId
) {
	wait_api ();

	ChampionArray * champArray = lolClient->lol->championArray;

	if (teammateId > champArray->teammatesCount || teammateId < 0) {
		dbg ("TeammateId (%d) is greater than teammates count (%d).",
			teammateId, champArray->teammatesCount);
		return false;
	}

	return true;
}


/*
 * Description            : Retrieve the teammate champion position
 * __in__  int teammateId : The target teammate ID
 * __out__ float * x      : A pointer to the X position
 * __out__ float * y      : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_teammate_position (
	__in__  int teammateId,
	__out__ float * x,
	__out__ float * y
) {
	wait_api ();

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = lolClient->lol->championArray->teammates[teammateId];
	Position * teammatePosition = LoLProcess_get_addr (teammate, currentPosition);

	*x = teammatePosition->x;
	*y = teammatePosition->y;
}


/*
 * Description               : Retrieve teammate champion health points information
 * __in__  int teammateId    : The target teammate ID
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

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = lolClient->lol->championArray->teammates[teammateId];

	float *teammateCurrentHP = (float *) LoLProcess_get_addr (teammate, curHP);
	float *teammateMaximumHP = (float *) LoLProcess_get_addr (teammate, maxHP);

	*currentHP = *teammateCurrentHP;
	*maximumHP = *teammateMaximumHP;
}


/*
 * Description                : Retrieve teammate summoner name.
 * __in__  int teammateId     : The target teammate ID
 * __in__ char * summonerName : A sequence of bytes containing the summoner name of the
 *                                 target teammate (16 bytes maximum)
 */
EXPORT_FUNCTION void
get_teammate_summoner_name (
	__in__  int teammateId,
	__in__ char * summonerName
) {
	wait_api ();

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = lolClient->lol->championArray->teammates[teammateId];
	char * teammateSummonerName = (char *) LoLProcess_get_addr (teammate, summonerName);

	memcpy (summonerName, teammateSummonerName, 16);
}


/** =================================================================================
 ** ==================================== GUI APIs ===================================
 ** ================================================================================= **/

/*
 * Description     : Retrieve the position of the minimap on the screen
 * __out__ int * x : A pointer to the X position
 * __out__ int * y : A pointer to the Y position
 */
EXPORT_FUNCTION void
get_minimap_screen_position (
	__out__ int * x,
	__out__ int * y
) {
	wait_api ();

	GUIMinimap * guiMinimap = lolClient->lol->guiMenu->guiMinimap;
	Position2D * minimapScreenPosition = LoLProcess_get_addr (guiMinimap, screenPosition);

	int windowX, windowY;
	window_get_position (lolClient->hwnd, &windowX, &windowY);

	*x = windowX + minimapScreenPosition->x;
	*y = windowY + minimapScreenPosition->y;
}


/*
 * Description : Check if the mouse is hovering the minimap
 * Return      : bool True on success, false otherwise.
 */
EXPORT_FUNCTION bool
is_cursor_hovering_minimap (
	void
) {
	int minimapX, minimapY;
	get_minimap_screen_position (&minimapX, &minimapY);

	int cursorX, cursorY;
	get_cursor_screen_position (&cursorX, &cursorY);

	return (cursorX >= minimapX && cursorY >= minimapY);
}




/** =======================================================================================
 ** ==================================== Summoner APIs ====================================
 ** ======================================================================================= **/


/*
 * Description : Retrieve the current summoner name
 * __in__ char * summonerName : A sequence of bytes containing the summoner name of the
 *                              target teammate (16 bytes maximum)
 */
EXPORT_FUNCTION void
get_current_summoner_name (
	__in__ char * summonerName
) {
	wait_api ();

	HeroClient * currentChampion = lolClient->lol->heroClient;
	char * currentSummonerName = LoLProcess_get_addr (currentChampion, summonerName);

	memcpy (summonerName, currentSummonerName, 16);
}


/** =================================================================================
 ** ================================= GameClock APIs ================================
 ** ================================================================================= **/


/*
 * Description : Get the current game time (as seconds)
 * Return      : float the current time as seconds
 */
EXPORT_FUNCTION float
get_game_time (
	void
) {
	wait_api ();

	GameClock * gameClock = lolClient->lol->gameClock;
	float *currentTimeSeconds = LoLProcess_get_addr (gameClock, gameTimeSeconds);

	return *currentTimeSeconds;
}


/** =======================================================================================
 ** ====================================== Chat APIs ======================================
 ** ======================================================================================= **/

/*
 * Description : Get the next line of the chat received since the last time called.
 * Return      : char * : A line of chat, or NULL if no message has been posted since the last time called.
 */
EXPORT_FUNCTION char *
get_chat_message (
	void
) {
	wait_api ();

	HudChat * hudChat = lolClient->lol->playerHUD->hudChat;

	// No new message
	if (bb_queue_get_length (&hudChat->chatMessages) <= 0) {
		return NULL;
	}

	// Return the first message of the queue (FIFO)
	return bb_queue_get_first (&hudChat->chatMessages);
}

/*
 * Description       : Log a message to the HudChat
 * char * message    : A message to add in the chat
 * int messageLength : The length of the message
 */
EXPORT_FUNCTION void
log_chat_message (
	char * message,
	int messageLength
) {
	wait_api ();

	HudChat * hudChat = lolClient->lol->playerHUD->hudChat;

	// Check if the HudChat pointer is correct
	if (!hudChat->pThis) {
		warn ("Cannot add message until a reference to the HudChat has been found.");
		return;
	}

	if (messageLength == -1) {
		messageLength = strlen (message);
	}

	HudChat_addMessage ((void *) hudChat->pThis, message, messageLength);
}

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
EXPORT_FUNCTION int
create_rectangle (
	int x, int y,
	int w, int h,
	byte r, byte g, byte b
) {
	wait_api ();
	wait_directx ();

	D3D9Object * object = D3D9ObjectFactory_createD3D9Object (D3D9_OBJECT_RECTANGLE);
	if (!D3D9ObjectRect_init (object, x, y, w, h, r, g, b)) {
		return -1;
	}

	return object->id;
}

/*
 * Description            : Create a new text displayed on the screen
 * char * string          : String of the text
 * int x, y               : {x, y} position of the text
 * byte r, byte g, byte b : color of the text
 * int fontSize           : the size of the font
 * char * fontFamily      : The name of the family font. If NULL, "Arial" is used.
 * Return                 : A unique ID handle of your text object
 */
EXPORT_FUNCTION int
create_text (
	char * string,
	int x, int y,
	byte r, byte g, byte b,
	int fontSize,
	char * fontFamily
) {
	wait_api ();
	wait_directx ();

	D3D9Object * object = D3D9ObjectFactory_createD3D9Object (D3D9_OBJECT_TEXT);
	IDirect3DDevice9 * pDevice = lolClient->dx->pDevice;

	if (!D3D9ObjectText_init (object, pDevice, x, y, r, g, b, string, fontSize, fontFamily)) {
		return -1;
	}

	return object->id;
}

/*
 * Description     : Create a new sprite displayed on the screen
 * char * filePath : Absolute or relative path of the image (.bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga)
 * int x, y        : {x, y} position of the image
 # float opacity   : opacity of the image, value between 0.0 and 1.0
 * Return          : A unique ID handle of your sprite object
 */
EXPORT_FUNCTION int
create_sprite (
	char *filePath,
	int x, int y,
	float opacity
) {
	wait_api ();
	wait_directx ();

	D3D9Object * object = D3D9ObjectFactory_createD3D9Object (D3D9_OBJECT_SPRITE);
	IDirect3DDevice9 * pDevice = lolClient->dx->pDevice;

	if (!D3D9ObjectSprite_init (object, pDevice, filePath, x, y, opacity)) {
		return -1;
	}

	return object->id;
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
	wait_directx ();

	D3D9ObjectFactory_show (id);
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
	wait_directx ();

	D3D9ObjectFactory_show_all ();
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
	wait_directx ();

	D3D9ObjectFactory_hide (id);
}


/*
 * Description : Show all hidden objects. Don't do anything with those already shown.
 * Return      : void
 */
EXPORT_FUNCTION void
hide_all_objects (
	void
) {
	wait_api ();
	wait_directx ();

	D3D9ObjectFactory_hide_all ();
}

/*
 * Description : Delete a specific object on the screen
 * int id      : The unique handle of the object to delete
 * Return      : void
 */
EXPORT_FUNCTION void
delete_object (
	int id
) {
	wait_api ();
	wait_directx ();

	D3D9ObjectFactory_delete (id);
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
	wait_directx ();

	D3D9ObjectFactory_delete_all ();
}


/** =======================================================================================
 ** ==================================== Internal APIs ====================================
 ** ======================================================================================= **/


/*
 * Description : Check if the API has been correctly injected into LoL process
 * Return      : true on successfully injected, false on failure
 */
EXPORT_FUNCTION bool
check_api (
	void
) {
	return (
		(lolClient != NULL)
	&&  (lolClient->state == STATE_READY || lolClient->state == STATE_TESTING));
}

/*
 * Description : Check if the API has retrieved the directx handle
 * Return      : true on success, false otherwise
 */
EXPORT_FUNCTION bool
check_directx (
	void
) {
	return (lolClient->dx->pDevice != NULL);
}


/*
 * Description : Wait for the API to be in a ready state (blocking)
 */
EXPORT_FUNCTION void
wait_api (
	void
) {
	while (!check_api ()) {
		dbg ("LoLClient is injecting LoLProcess. Please wait...");
		Sleep (100);
	}
}

/*
 * Description : Wait for the DirectX handle to be in a ready state (blocking)
 */
EXPORT_FUNCTION void
wait_directx (
	void
) {
	while (!check_directx ()) {
		dbg ("LoLClient is waiting for DirectX. Please wait...");
		Sleep (100);
	}
}

/*
 * Description                 : Set the current used lolClient instance
 * __in__ LoLProcess *instance : Set the global lolClient value to this argument
 * Note                        : /!\ Use it only if you know what you are doing !
 */
void
set_LoLProcess (
	__in__ LoLProcess *instance
) {
	lolClient = instance;
}


/*
 * Description         : Get the current used lolClient instance
 * Return LoLProcess * : A pointer to the current lolClient instance
 * Note                : /!\ Use it only if you know what you are doing !
 */
LoLProcess *
get_LoLProcess (
	void
) {
	return lolClient;
}
