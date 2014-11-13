#include "LoLServerAPI.h"
#include "LoLServerInterface.h"

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "LoLServerAPI"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new LoLServerAPI structure.
 * EasySocketListened *client : A pointer to the client data
 */
void
LoLServerAPI_handle_request (
	EasySocketListened *client
) {
	LoLAPIRequest request;
	memcpy (&request, client->buffer, sizeof(LoLAPIRequest));

	switch (request)
	{
		// Camera APIs
		case REQUEST_GET_CAMERA_POSITION: {
			PositionPacket packet;
			get_camera_position (&packet.position.x, &packet.position.y);
			es_send (EASY_SOCKET (client), &packet, sizeof(PositionPacket));
		} break;

		case REQUEST_SET_CAMERA_POSITION:
		break;

		case REQUEST_SET_CAMERA_CLIENT_ENABLED:
		break;

		case REQUEST_SET_CAMERA_ANGLE:
		break;

		case REQUEST_SET_CAMERA_ZOOM:
		break;


		// Cursor APIs
		case REQUEST_GET_CURSOR_SCREEN_POSITION:
		break;

		case REQUEST_GET_DESTINATION_POSITION:
		break;

		case REQUEST_IS_LEFT_MOUSE_BUTTON_PRESSED:
		break;

		case REQUEST_IS_LEFT_MOUSE_BUTTON_CLICK:
		break;

		case REQUEST_IS_RIGHT_MOUSE_BUTTON_PRESSED:
		break;

		case REQUEST_IS_RIGHT_MOUSE_BUTTON_CLICK:
		break;


		// Keyboard APIs
		case REQUEST_IS_SPACE_PRESSED:
		break;


		// Champion APIs
		case REQUEST_GET_CHAMPION_POSITION:
		break;

		case REQUEST_GET_CHAMPION_HP:
		break;

		case REQUEST_GET_CHAMPION_TEAM:
		break;


		// Teammates APIs
		case REQUEST_GET_TEAMMATES_COUNT:
		break;

		case REQUEST_CHECK_TEAMMATE_ID:
		break;

		case REQUEST_GET_TEAMMATE_POSITION:
		break;

		case REQUEST_GET_TEAMMATE_HP:
		break;

		case REQUEST_GET_TEAMMATE_SUMMONER_NAME:
		break;


		// Minimap APIs
		case REQUEST_GET_MINIMAP_SCREEN_POSITION:
		break;

		case REQUEST_IS_CURSOR_HOVERING_MINIMAP:
		break;


		// Summoner APIs
		case REQUEST_GET_CURRENT_SUMMONER_NAME:
		break;


		// Game APIs
		case REQUEST_GET_GAME_TIME:
		break;

		default :
			dbg ("Unhandled request = %x", request);
		break;
	}
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
		while (!this->closed) {
			Sleep (1);
		}
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
