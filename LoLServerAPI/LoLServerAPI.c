#include "LoLServerAPI.h"
#include "LoLServerInterface.h"
#include "LoLAPI/LoLAPIRequest.h"

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "LoLServerAPI"
#include "dbg/dbg.h"


/*
 * Description 	: Handle a request from the client
 * EasySocketListened *client : A pointer to the client data
 */
void
LoLServerAPI_handle_request (
	EasySocketListened *client
) {
	LoLAPIPacket packet;
	memcpy (&packet, client->buffer, sizeof(packet));

	if (!LoLAPIRequest_is_valid (packet.request)) {
		packet.request = REQUEST_FAIL;
	}

	// Read the request
	switch (packet.request)
	{
		// Camera APIs
		case REQUEST_GET_CAMERA_POSITION:
			get_camera_position (&packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_SET_CAMERA_POSITION:
			set_camera_position (packet.gamePositionPacket.pos.x, packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_SET_CAMERA_CLIENT_ENABLED:
			set_camera_client_enabled (packet.booleanPacket.value);
		break;

		case REQUEST_GET_CAMERA_ANGLE:
			get_camera_angle (&packet.anglePacket.x, &packet.anglePacket.y);
		break;

		case REQUEST_SET_CAMERA_ANGLE:
			set_camera_angle (packet.anglePacket.x, packet.anglePacket.y);
		break;

		case REQUEST_GET_CAMERA_ZOOM:
			packet.floatPacket.value = get_camera_zoom ();
		break;

		case REQUEST_SET_CAMERA_ZOOM:
			set_camera_zoom (packet.floatPacket.value);
		break;


		// Cursor APIs
		case REQUEST_GET_CURSOR_POSITION:
			get_cursor_position (&packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_GET_CURSOR_SCREEN_POSITION:
			get_cursor_screen_position (&packet.screenPositionPacket.x, &packet.screenPositionPacket.y);
		break;

		case REQUEST_GET_DESTINATION_POSITION:
			get_destination_position (&packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_IS_LEFT_MOUSE_BUTTON_PRESSED:
			packet.booleanPacket.value = is_left_mouse_button_pressed ();
		break;

		case REQUEST_IS_LEFT_MOUSE_BUTTON_CLICK:
			packet.booleanPacket.value = is_left_mouse_button_click ();
		break;

		case REQUEST_IS_RIGHT_MOUSE_BUTTON_PRESSED:
			packet.booleanPacket.value = is_right_mouse_button_pressed ();
		break;

		case REQUEST_IS_RIGHT_MOUSE_BUTTON_CLICK:
			packet.booleanPacket.value = is_right_mouse_button_click ();
		break;


		// Keyboard APIs
		case REQUEST_IS_SPACE_PRESSED:
			packet.booleanPacket.value = is_space_pressed ();
		break;


		// Champion APIs
		case REQUEST_GET_CHAMPION_POSITION:
			get_champion_position (&packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_GET_CHAMPION_HP:
			get_champion_hp (&packet.hpPacket.curHP, &packet.hpPacket.maxHP);
		break;

		case REQUEST_GET_CHAMPION_TEAM:
			packet.intPacket.value = get_champion_team ();
		break;


		// Teammates APIs
		case REQUEST_GET_TEAMMATES_COUNT:
			packet.intPacket.value = get_teammates_count ();
		break;

		case REQUEST_CHECK_TEAMMATE_ID:
			packet.booleanPacket.value = check_teammate_id (packet.teammateId);
		break;

		case REQUEST_GET_TEAMMATE_POSITION:
			get_teammate_position (packet.teammateId, &packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_GET_TEAMMATE_HP:
			get_teammate_hp (packet.teammateId, &packet.hpPacket.curHP, &packet.hpPacket.maxHP);
		break;

		case REQUEST_GET_TEAMMATE_SUMMONER_NAME:
			get_teammate_summoner_name (packet.teammateId, packet.stringPacket.str);
		break;

		// Minimap APIs
		case REQUEST_GET_MINIMAP_SCREEN_POSITION:
			get_minimap_screen_position (&packet.screenPositionPacket.x, &packet.screenPositionPacket.y);
		break;

		case REQUEST_IS_CURSOR_HOVERING_MINIMAP:
			packet.booleanPacket.value = is_cursor_hovering_minimap ();
		break;


		// Summoner APIs
		case REQUEST_GET_CURRENT_SUMMONER_NAME:
			get_current_summoner_name (packet.stringPacket.str);
		break;


		// Game APIs
		case REQUEST_GET_GAME_TIME:
			packet.floatPacket.value = get_game_time ();
		break;

		default :
			dbg ("Unhandled request = %x", packet.request);
		break;
	}

	// Answer
	es_send (EASY_SOCKET (client), &packet, sizeof (packet));
}

/*
 * Description 	: Free the client that just disconnected
 * EasySocketListened *client : A pointer to the client data
 */
void LoLServerAPI_client_finish (
	EasySocketListened *client
) {
	es_listener_free (client, free);
}


/*
 * Description 	: Allocate a new LoLServerAPI structure.
 * Return		: A pointer to an allocated LoLServerAPI.
 */
LoLServerAPI *
LoLServerAPI_new (void)
{
	LoLServerAPI *this;

	if ((this = calloc (1, sizeof(LoLServerAPI))) == NULL)
		return NULL;

	if (!LoLServerAPI_init (this)) {
		LoLServerAPI_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated LoLServerAPI structure.
 * LoLServerAPI *this : An allocated LoLServerAPI to initialize.
 * Return : true on success, false on failure.
 */
bool
LoLServerAPI_init (
	LoLServerAPI *this
) {
	es_init ();

	if ((this->serverSocket = es_server_new (LOLAPI_PORT, 1000)) == NULL) {
        warn ("Cannot create API server.");
        return false;
	}

	this->closed = false;

	return true;
}


/*
 * Description : Main loop of the API server
 * LoLServerAPI *this : An allocated LoLServerAPI
 * Return : void
 */
void
LoLServerAPI_main (
	LoLServerAPI *this
) {
	EasySocketListened *client = NULL;

	do {
		if ((client = es_accept (this->serverSocket, 1024)) != NULL) {
			es_send (EASY_SOCKET(client), "READY", -1);
			es_listener (client, LoLServerAPI_handle_request, LoLServerAPI_client_finish);
		}
	} while (client != NULL);
}

/*
 * Description : Free an allocated LoLServerAPI structure.
 * LoLServerAPI *this : An allocated LoLServerAPI to free.
 */
void
LoLServerAPI_free (
	LoLServerAPI *this
) {
	if (this != NULL) {
		LoLProcess_free (get_LoLProcess ());
		es_close (this->serverSocket);
		free (this);
	}
}


/*
 * Description : Unit tests checking if a LoLServerAPI is coherent
 * LoLServerAPI *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLServerAPI_test (
	LoLServerAPI *this
) {

	return true;
}
