#include "LoLServerAPI.h"
#include "LoLServerInterface.h"
#include "LoLAPI/LoLAPIRequest.h"

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "LoLServerAPI"
#include "dbg/dbg.h"


// Global connection with the client
LoLServerAPI * serverAPI = NULL;


/*
 * Description 	              : Handle a request from the client
 * EasySocketListened *client : A pointer to the client data
 */
void
LoLServerAPI_handle_request (
	EasySocketListened *client
) {
	LoLAPIPacket packet;
	void *object = NULL;
	size_t objectSize = 0;
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

		case REQUEST_SET_DEFAULT_CAMERA_ENABLED:
			set_default_camera_enabled (packet.booleanPacket.value);
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
		case REQUEST_IS_KEY_PRESSED:
			packet.booleanPacket.value = is_key_pressed (packet.bytePacket.value);
		break;

		case REQUEST_IS_KEY_TYPED:
			packet.booleanPacket.value = is_key_typed (packet.bytePacket.value);
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
			packet.booleanPacket.value = check_teammate_id (packet.id);
		break;

		case REQUEST_GET_TEAMMATE_POSITION:
			get_teammate_position (packet.id, &packet.gamePositionPacket.pos.x, &packet.gamePositionPacket.pos.y);
		break;

		case REQUEST_GET_TEAMMATE_HP:
			get_teammate_hp (packet.id, &packet.hpPacket.curHP, &packet.hpPacket.maxHP);
		break;

		case REQUEST_GET_TEAMMATE_SUMMONER_NAME:
			get_teammate_summoner_name (packet.id, packet.bufferPacket.buffer);
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
			get_current_summoner_name (packet.bufferPacket.buffer);
		break;


		// Chat APIs
		case REQUEST_GET_CHAT_MESSAGE:
			if ((object = get_chat_message ()) != NULL) {
				objectSize = strlen (object);
				packet.objectPacket.size = objectSize;
			}
		break;

		case REQUEST_LOG_CHAT_MESSAGE: {
			// Receive the chat message right after the first packet
			char * message = calloc (1, packet.objectPacket.size + 1);
			es_recv_buffer (EASY_SOCKET (client), message, packet.objectPacket.size);
			log_chat_message (message, packet.objectPacket.size);
		} break;


		// Drawing APIs
		case REQUEST_CREATE_RECTANGLE: {
			packet.intPacket.value = create_rectangle (
				packet.rectPacket.x, packet.rectPacket.y,
				packet.rectPacket.w, packet.rectPacket.h,
				packet.rectPacket.r, packet.rectPacket.g, packet.rectPacket.b
			);
		} break;

		case REQUEST_CREATE_TEXT: {
			// Receive the string the next packet
			// Receive the font family in the next one
			char * string = calloc (1, packet.textPacket.stringLen + 1);
			es_recv_buffer (EASY_SOCKET (client), string, packet.textPacket.stringLen);
			char * fontFamily = calloc (1, packet.textPacket.fontFamilyLen + 1);
			es_recv_buffer (EASY_SOCKET (client), fontFamily, packet.textPacket.fontFamilyLen);

			packet.intPacket.value = create_text (
				string,
				packet.textPacket.x, packet.textPacket.y,
				packet.textPacket.r, packet.textPacket.g, packet.textPacket.b,
				packet.textPacket.opacity,
				packet.textPacket.fontSize,
				fontFamily
			);

			free (string);
			free (fontFamily);
		} break;

		case REQUEST_CREATE_SPRITE: {
			// Receive the file path in the next packet
			char * filePath = calloc (1, packet.spritePacket.filePathLen + 1);
			es_recv_buffer (EASY_SOCKET (client), filePath, packet.spritePacket.filePathLen);

			packet.intPacket.value = create_sprite (
				filePath,
				packet.spritePacket.x, packet.spritePacket.y,
				packet.spritePacket.opacity
			);

			free (filePath);
		} break;

		case REQUEST_MOVE_OBJECT:
			move_object (packet.id, packet.screenPositionPacket.x, packet.screenPositionPacket.y);
		break;

		case REQUEST_RECT_OBJECT_SET: {
			rect_object_set (packet.id, packet.rectPacket.r, packet.rectPacket.g, packet.rectPacket.b, packet.rectPacket.w, packet.rectPacket.h);
		} break;


		case REQUEST_TEXT_OBJECT_SET: {
			// Receive the string the next packet
			char * string = calloc (1, packet.textPacket.stringLen + 1);
			es_recv_buffer (EASY_SOCKET (client), string, packet.textPacket.stringLen);
			text_object_set (packet.id, string, packet.textPacket.r, packet.textPacket.g, packet.textPacket.b, packet.textPacket.opacity);
			free (string);
		} break;

		case REQUEST_SPRITE_OBJECT_SET: {
			sprite_object_set (packet.id, packet.spritePacket.opacity);
		} break;

		case REQUEST_DELETE_OBJECT:
			delete_object (packet.intPacket.value);
		break;

		case REQUEST_DELETE_ALL_OBJECTS:
			delete_all_objects ();
		break;

		case REQUEST_SHOW_OBJECT:
			show_object (packet.intPacket.value);
		break;

		case REQUEST_SHOW_ALL_OBJECTS:
			show_all_objects ();
		break;

		case REQUEST_HIDE_OBJECT:
			hide_object (packet.intPacket.value);
		break;

		case REQUEST_HIDE_ALL_OBJECTS:
			hide_all_objects ();
		break;

		case REQUEST_GET_HOVERED_OBJECT:
			packet.intPacket.value = get_hovered_object ();
		break;

		// Game APIs
		case REQUEST_GET_GAME_TIME:
			packet.floatPacket.value = get_game_time ();
		break;


		// Internal APIs
		case REQUEST_EJECT_API:
			LoLServerAPI_eject (serverAPI);
			strncpy (packet.bufferPacket.buffer, LOLAPI_STATUS_EXIT, sizeof(packet.bufferPacket.buffer));
			es_send (EASY_SOCKET (client), &packet, sizeof (packet));
			es_close (EASY_SOCKET (client));
			return;
		break;


		// Errors
		case REQUEST_FAIL :
		break;

		default :
			if (LoLAPIRequest_is_valid (packet.request)) {
				dbg ("Unhandled request = %s", LoLAPIRequest_to_string (packet.request));
			} else {
				dbg ("Unhandled request = %x", packet.request);
			}
		break;
	}

	// Answer to the client the initial packet
	es_send (EASY_SOCKET (client), &packet, sizeof(packet));

	// Send a dynamic sized object right after the initial packet if the object is initialized
	if (object != NULL && objectSize != 0) {
		es_send (EASY_SOCKET (client), object, objectSize);
	}
}

/*
 * Description 	              : Free the client that just disconnected
 * EasySocketListened *client : A pointer to the client data
 */
void LoLServerAPI_client_finish (
	EasySocketListened *client
) {
	Sleep (1000);
	es_listener_free (client, free);
}


/*
 * Description 	  : Allocate a new LoLServerAPI structure.
 * Return		  : A pointer to an allocated LoLServerAPI.
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

	serverAPI = this;

	return this;
}


/*
 * Description        : Clean the memory from the LoLProcess before ejecting the server DLL
 * LoLServerAPI *this : An allocated LoLServerAPI
 * Return             : void
 */
void
LoLServerAPI_eject (
	LoLServerAPI *this
) {
	log_chat_message ("<font color=\"#ff3333\">LoLClientAPI has been unloaded.</font>", -1);

	HookEngine_unhook_all ();
	dbg ("Functions correctly unhooked!");

	this->running = false;
}


/*
 * Description         : Initialize an allocated LoLServerAPI structure.
 * LoLServerAPI *this  : An allocated LoLServerAPI to initialize.
 * Return              : true on success, false on failure.
 */
bool
LoLServerAPI_init (
	LoLServerAPI *this
) {
	es_init ();

	if ((this->serverSocket = es_server_new (LOLAPI_PORT, 1337)) == NULL) {
        warn ("Cannot create API server.");
        return false;
	}

	es_set_blocking (this->serverSocket, false);
	this->closed = false;

	return true;
}


/*
 * Description          : Main loop of the API server
 * LoLServerAPI *this   : An allocated LoLServerAPI
 * Return               : void
 */
void
LoLServerAPI_main (
	LoLServerAPI *this
) {
	EasySocketListened *client = NULL;
	this->running = true;

	while (this->running)
	{
		if ((client = es_accept (this->serverSocket, 1024, true)) != NULL)
		{
			es_set_blocking (EASY_SOCKET (client), true);
			es_send (EASY_SOCKET (client), LOLAPI_STATUS_READY, -1);
			es_listener (client, LoLServerAPI_handle_request, LoLServerAPI_client_finish);
		}

		Sleep (1000);
	}
}


/*
 * Description         : Free an allocated LoLServerAPI structure.
 * LoLServerAPI *this  : An allocated LoLServerAPI to free.
 */
void
LoLServerAPI_free (
	LoLServerAPI *this
) {
	if (this != NULL)
	{
		if (this->serverSocket) {
			es_close (this->serverSocket);
		}

		free (this);
	}
}


/*
 * Description         : Unit tests checking if a LoLServerAPI is coherent
 * LoLServerAPI *this  : The instance to test
 * Return              : true on success, false on failure
 */
bool
LoLServerAPI_test (
	LoLServerAPI *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	return true;
}
