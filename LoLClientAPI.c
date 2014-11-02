#include "LolClientAPI.h"
#include "LoLProcess/LoLProcess.h"
#include <stdint.h>

#define __DEBUG_OBJECT__ "LoLClientAPI"
#include "dbg/dbg.h"


// LoLClientAPI singleton
LoLProcess * LoLClientAPI = NULL;


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
	waitForAPI ();

	HudCamera * hudCamera      = LoLClientAPI->hudManager->hudCamera;
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
	waitForAPI ();

	HudCamera * hudCamera      = LoLClientAPI->hudManager->hudCamera;
	Position  * cameraPosition = LoLProcess_get_addr (hudCamera, cameraPosition);

	cameraPosition->x = x;
	cameraPosition->y = y;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			LoLClientAPI->process->proc,
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
	waitForAPI ();

	HudCameraSettings * hudCameraSettings = LoLClientAPI->hudManager->hudCameraSettings;
	int * cameraActivated = LoLProcess_get_addr (hudCameraSettings, cameraActivated);

	*cameraActivated = enabled;

	#ifdef API_EXECUTABLE
		WriteProcessMemory (
			LoLClientAPI->process->proc,
			LoLProcess_get_remote_addr (hudCameraSettings, cameraActivated),
			cameraActivated,
			sizeof (*cameraActivated),
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
	waitForAPI ();

	HudCursorTarget * hudCursorTarget = LoLClientAPI->hudManager->hudCursorTarget;
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
	waitForAPI ();

	HudCursorTarget * hudCursorTarget = LoLClientAPI->hudManager->hudCursorTarget;
	Position * rightClickPosition = LoLProcess_get_addr (hudCursorTarget, rightClickPosition);

	*x = rightClickPosition->x;
	*y = rightClickPosition->y;
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
	waitForAPI ();

	HeroClient * currentChampion = LoLClientAPI->heroClient;
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
	waitForAPI ();

	HeroClient * currentChampion = LoLClientAPI->heroClient;
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
	waitForAPI ();

	HeroClient * currentChampion = LoLClientAPI->heroClient;
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
	waitForAPI ();

	ChampionArray * champArray = LoLClientAPI->championArray;

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
	waitForAPI ();

	ChampionArray * champArray = LoLClientAPI->championArray;

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
	waitForAPI ();

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = LoLClientAPI->championArray->teammates[teammateId];
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
	waitForAPI ();

	if (!check_teammate_id (teammateId)) {
		return;
	}

	Unit * teammate = LoLClientAPI->championArray->teammates[teammateId];

	float *teammateCurrentHP = (float *) LoLProcess_get_addr (teammate, curHP);
	float *teammateMaximumHP = (float *) LoLProcess_get_addr (teammate, maxHP);

	*currentHP = *teammateCurrentHP;
	*maximumHP = *teammateMaximumHP;
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
	waitForAPI ();

	if (!check_teammate_id (teammateId)) {
		return NULL;
	}

	Unit * teammate = LoLClientAPI->championArray->teammates[teammateId];
	char * teammateSummonerName = (char *) LoLProcess_get_addr (teammate, summonerName);

	return teammateSummonerName;
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
	waitForAPI ();

	GUIMinimap * guiMinimap = LoLClientAPI->guiMenu->guiMinimap;
	Position2D * minimapScreenPosition = LoLProcess_get_addr (guiMinimap, screenPosition);

	int windowX, windowY;
	window_get_position (LoLClientAPI->process->hwnd, &windowX, &windowY);

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
 * Return : char * The summoner name
 */
EXPORT_FUNCTION char *
get_current_summoner_name (
	void
) {
	waitForAPI ();

	HeroClient * currentChampion = LoLClientAPI->heroClient;
	char * currentSummonerName = LoLProcess_get_addr (currentChampion, summonerName);

	return currentSummonerName;
}


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
) {
	return (
		(LoLClientAPI != NULL)
	&&  (LoLClientAPI->state == STATE_READY || LoLClientAPI->state == STATE_TESTING));
}


/*
 * Description : Wait for the API to be in ready state
 * Return : void
 */
EXPORT_FUNCTION void
waitForAPI (
	void
) {
	while (!check_api ()) {
		dbg ("LoLClientAPI is injecting LoLProcess. Please wait...");
		Sleep (1000);
	}
}


/*
 * Description : Set the current used LoLClientAPI instance
 * __in__ LoLProcess *instance : Set the global LoLClientAPI value to this argument
 * Note : /!\ Use it only if you know what you are doing !
 */
EXPORT_FUNCTION void
set_LoLClientAPI (
	__in__ LoLProcess *instance
) {
	LoLClientAPI = instance;
}


/*
 * Description : Get the current used LoLClientAPI instance
 * Return LoLProcess * : A pointer to the current LoLClientAPI instance
 * Note : /!\ Use it only if you know what you are doing !
 */
EXPORT_FUNCTION LoLProcess *
get_LoLClientAPI (
	void
) {
	return LoLClientAPI;
}
