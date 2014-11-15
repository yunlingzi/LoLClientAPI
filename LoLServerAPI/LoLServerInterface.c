#include "LoLServerAPI/LoLServerInterface.h"
#include "LoLProcess/LoLProcess.h"
#include <stdint.h>

#define __DEBUG_OBJECT__ "LoLServerInterface"
#include "dbg/dbg.h"


// Singleton
LoLProcess * client = NULL;


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

	HudCamera * hudCamera      = client->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	*x = cameraPosition->x;
	*y = cameraPosition->y;
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

	HudCamera * hudCamera      = client->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	cameraPosition->x = x;
	cameraPosition->y = y;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			client->process->proc,
			LoLProcess_get_remote_addr (hudCamera, cameraPosition),
			cameraPosition,
			sizeof (*cameraPosition),
			NULL
		);
	#endif
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
	wait_api ();

	HudCameraSettings * hudCameraSettings = client->hudManager->hudCameraSettings;
	int * cameraActivated = LoLProcess_get_addr (hudCameraSettings, cameraActivated);

	*cameraActivated = enabled;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			client->process->proc,
			LoLProcess_get_remote_addr (hudCameraSettings, cameraActivated),
			cameraActivated,
			sizeof (*cameraActivated),
			NULL
		);
	#endif
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

	HudCamera * hudCamera = client->hudManager->hudCamera;
	HudCameraAngle * hudCameraAngle = LoLProcess_get_addr (hudCamera, cameraAngle);

	*angleX = hudCameraAngle->x;
	*angleY = hudCameraAngle->y;
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

	HudCamera * hudCamera = client->hudManager->hudCamera;
	HudCameraAngle * cameraAngle = LoLProcess_get_addr (hudCamera, cameraAngle);

	cameraAngle->x = angleX;
	cameraAngle->y = angleY;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			client->process->proc,
			LoLProcess_get_remote_addr (hudCamera, cameraAngle),
			cameraAngle,
			sizeof (*cameraAngle),
			NULL
		);
	#endif
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

	HudCamera * hudCamera = client->hudManager->hudCamera;
	HudCameraZoom * cameraZoom = LoLProcess_get_addr (hudCamera, cameraZoom);

	return cameraZoom->curValue;
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

	HudCamera * hudCamera = client->hudManager->hudCamera;
	HudCameraZoom * cameraZoom = LoLProcess_get_addr (hudCamera, cameraZoom);

	cameraZoom->targetValue = zoomValue;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			client->process->proc,
			LoLProcess_get_remote_addr (hudCamera, cameraZoom),
			cameraZoom,
			sizeof (*cameraZoom),
			NULL
		);
	#endif
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

	HudCursorTarget * hudCursorTarget = client->hudManager->hudCursorTarget;
	Position        * cursorPosition  = LoLProcess_get_addr (hudCursorTarget, posRaw);

	*x = cursorPosition->x;
	*y = cursorPosition->y;
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
	POINT point;
	GetCursorPos (&point);

	*x = point.x;
	*y = point.y;
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

	HudCursorTarget * hudCursorTarget = client->hudManager->hudCursorTarget;
	Position * rightClickPosition = LoLProcess_get_addr (hudCursorTarget, rightClickPosition);

	*x = rightClickPosition->x;
	*y = rightClickPosition->y;
}


/*
 * Description : Check if the left mouse button is pressed
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_pressed (
	void
) {
	return GetKeyState (VK_LBUTTON) < 0;
}


/*
 * Description : Check if the left mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_left_mouse_button_click (
	void
) {
	static int leftMouseButtonState = 0;

	if (is_left_mouse_button_pressed ()) {
		// The button has been pressed but not released yet
		leftMouseButtonState = 1;
		return false;
	}

	if (leftMouseButtonState && !is_left_mouse_button_pressed ()) {
		// The button has been pressed but isn't pressed anymore
		leftMouseButtonState = 0;
		return true;
	}

	// Nothing detected
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
	return GetKeyState (VK_RBUTTON) < 0;
}


/*
 * Description : Check if the right mouse button is clicked
 * Returns : true if pressed, false otherwise
 */
EXPORT_FUNCTION bool
is_right_mouse_button_click (
	void
) {
	static int rightMouseButtonState = 0;

	if (is_right_mouse_button_pressed ()) {
		// The button has been pressed but not released yet
		rightMouseButtonState = 1;
		return false;
	}

	if (rightMouseButtonState && !is_right_mouse_button_pressed ()) {
		// The button has been pressed but isn't pressed anymore
		rightMouseButtonState = 0;
		return true;
	}

	// Nothing detected
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
	return GetKeyState (VK_SPACE) < 0;
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

	HeroClient * currentChampion = client->heroClient;
	Position * currentChampionPosition = LoLProcess_get_addr (currentChampion, currentPosition);

	*x = currentChampionPosition->x;
	*y = currentChampionPosition->y;
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

	HeroClient * currentChampion = client->heroClient;
	float *currentChampionCurrentHP = (float *) LoLProcess_get_addr (currentChampion, curHP);
	float *currentChampionMaximumHP = (float *) LoLProcess_get_addr (currentChampion, maxHP);

	*currentHP = *currentChampionCurrentHP;
	*maximumHP = *currentChampionMaximumHP;
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

	HeroClient * currentChampion = client->heroClient;
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
 * Return : The number of allies in your team
 */
EXPORT_FUNCTION int
get_teammates_count (
	void
) {
	wait_api ();

	ChampionArray * champArray = client->championArray;

	return champArray->teammatesCount;
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

	ChampionArray * champArray = client->championArray;

	if (teammateId > champArray->teammatesCount || teammateId < 0) {
		dbg ("TeammateId (%d) is greater than teammates count (%d).",
			teammateId, champArray->teammatesCount);
		return false;
	}

	return true;
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

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = client->championArray->teammates[teammateId];
	Position * teammatePosition = LoLProcess_get_addr (teammate, currentPosition);

	*x = teammatePosition->x;
	*y = teammatePosition->y;
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

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = client->championArray->teammates[teammateId];

	float *teammateCurrentHP = (float *) LoLProcess_get_addr (teammate, curHP);
	float *teammateMaximumHP = (float *) LoLProcess_get_addr (teammate, maxHP);

	*currentHP = *teammateCurrentHP;
	*maximumHP = *teammateMaximumHP;
}


/*
 * Description : Retrieve teammate summoner name.
 * __in__  int teammateId : The target teammate ID
 * __in__ char * summonerName : A sequence of bytes containing the summoner name of the
 *                              target teammate (16 bytes maximum)
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

	Unit * teammate = client->championArray->teammates[teammateId];
	char * teammateSummonerName = (char *) LoLProcess_get_addr (teammate, summonerName);

	memcpy (summonerName, teammateSummonerName, 16);
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

	GUIMinimap * guiMinimap = client->guiMenu->guiMinimap;
	Position2D * minimapScreenPosition = LoLProcess_get_addr (guiMinimap, screenPosition);

	int windowX, windowY;
	window_get_position (client->process->hwnd, &windowX, &windowY);

	*x = windowX + minimapScreenPosition->x;
	*y = windowY + minimapScreenPosition->y;
}


/*
 * Description : Check if the mouse is hovering the minimap
 * Return : bool True on success, false otherwise.
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

	HeroClient * currentChampion = client->heroClient;
	char * currentSummonerName = LoLProcess_get_addr (currentChampion, summonerName);

	memcpy (summonerName, currentSummonerName, 16);
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

	GameClock * gameClock = client->gameClock;
	float *currentTimeSeconds = LoLProcess_get_addr (gameClock, gameTimeSeconds);

	return *currentTimeSeconds;
}


/** =======================================================================================
 ** ==================================== Internal APIs ====================================
 ** ======================================================================================= **/


/*
 * Description : Check if the API has been correctly injected into LoL process
 * Return : true on successfully injected, false on failure
 */
EXPORT_FUNCTION bool
check_api (
	void
) {
	return (
		(client != NULL)
	&&  (client->state == STATE_READY || client->state == STATE_TESTING));
}


/*
 * Description : Wait for the API to be in ready state
 * Return : void
 */
EXPORT_FUNCTION void
wait_api (
	void
) {
	while (!check_api ()) {
		dbg ("client is injecting LoLProcess. Please wait...");
		Sleep (100);
	}
}


/*
 * Description : Set the current used client instance
 * __in__ LoLProcess *instance : Set the global client value to this argument
 * Note : /!\ Use it only if you know what you are doing !
 */
EXPORT_FUNCTION void
set_LoLProcess (
	__in__ LoLProcess *instance
) {
	client = instance;
}


/*
 * Description : Get the current used client instance
 * Return LoLProcess * : A pointer to the current client instance
 * Note : /!\ Use it only if you know what you are doing !
 */
EXPORT_FUNCTION LoLProcess *
get_LoLProcess (
	void
) {
	return client;
}
