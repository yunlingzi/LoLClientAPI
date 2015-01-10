#include "LoLClientAPI.h"
#include "LoLClientInterface.h"
#include "LoLAPI/LoLAPIRequest.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "LoLClientAPI"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new LoLClientAPI structure.
 * Return		: A pointer to an allocated LoLClientAPI.
 */
LoLClientAPI *
LoLClientAPI_new (void)
{
	LoLClientAPI *this;

	if ((this = calloc (1, sizeof(LoLClientAPI))) == NULL)
		return NULL;

	if (!LoLClientAPI_init (this)) {
		LoLClientAPI_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Receive packet from the LoLServerAPI
 * LoLClientAPI *this : An allocated LoLClientAPI
 * LoLAPIPacket *packet : A packet to recieve
 * int packetSize : The size of the packet
 * Return : bool true on success, false otherwise
 */
bool
LoLClientAPI_recv (
	LoLClientAPI *this,
	LoLAPIPacket *packet,
	int packetSize
) {
	LoLAPIRequest originalRequest = packet->request;

	// And receive its response
	if (!es_recv_buffer (this->clientSocket, packet, packetSize)) {
		warn ("Error when receiving the last packet (API_RECV_ERROR).");
		this->lastError = API_RECV_ERROR;
		return false;
	}

	if (packet->request == REQUEST_FAIL) {
		warn ("Request failed received (REQUEST_FAIL).");
		this->lastError = API_REQUEST_FAIL;
		return false;
	}

	if (!LoLAPIRequest_is_valid (packet->request)) {
		warn ("Request received from the APIServer isn't supported : %d (API_REQUEST_INVALID).", packet->request);
		this->lastError = API_REQUEST_INVALID;
		return false;
	}

	// Check if the received answer type is the same than the requested one
	if (packet->request != originalRequest) {
		warn ("Not received the queried request. Client = <%s>, Server = <%s>) (API_REQUEST_UNSYNCHRONIZED).",
			LoLAPIRequest_to_string (originalRequest),
			LoLAPIRequest_to_string (packet->request)
		);

		this->lastError = API_REQUEST_UNSYNCHRONIZED;
		return false;
	}

	return true;
}


/*
 * Description : Send to the LoLServerAPI a given request
 * LoLClientAPI *this : An allocated LoLClientAPI
 * LoLAPIPacket *packet : A packet to send
 * int packetSize : The size of the packet
 * Return : bool true on success, false otherwise
 */
bool
LoLClientAPI_send (
	LoLClientAPI *this,
	LoLAPIPacket *packet,
	int packetSize
) {
	if (!LoLAPIRequest_is_valid (packet->request)) {
		warn ("Request sent to APIServer isn't valid : %d (API_REQUEST_INVALID).", packet->request);
		this->lastError = API_REQUEST_INVALID;
		return false;
	}

	// Send packet to the server ...
	if (es_send (this->clientSocket, packet, packetSize) == -1) {
		warn ("Error when sending the packet <%s> (API_SEND_ERROR).", LoLAPIRequest_to_string (packet->request));
		this->lastError = API_SEND_ERROR;
		return false;
	}

	return true;
}


/*
 * Description : Initialize an allocated LoLClientAPI structure.
 * LoLClientAPI *this : An allocated LoLClientAPI to initialize.
 * Return : true on success, false on failure.
 */
bool
LoLClientAPI_init (
	LoLClientAPI *this
) {
	es_init ();

	// Initiate the connection
	if ((this->clientSocket = es_client_new_from_ip ("127.0.0.1", LOLAPI_PORT)) == NULL) {
		warn ("LoLServerAPI not found.");
		this->clientSocket = NULL;
		return false;
	}

	// Receive status
	int answerSize;
	unsigned char * answer = es_recv (this->clientSocket, &answerSize);

	if (answerSize <= 0 || strncmp (answer, LOLAPI_STATUS_READY, answerSize) != 0) {
		warn ("Malformed LoLAPIServer status response. (answerSize = %d, answer = <%s>)", answerSize, answer);
		return false;
	}

	return true;
}


/*
 * Description : Free an allocated LoLClientAPI structure.
 * LoLClientAPI *this : An allocated LoLClientAPI to free.
 */
void
LoLClientAPI_free (
	LoLClientAPI *this
) {
	if (this != NULL)
	{
		if (this->clientSocket != NULL) {
			es_close (this->clientSocket);
		}

		free (this);
	}
}


/*
 * Description : Unit tests checking if a LoLClientAPI is coherent
 * LoLClientAPI *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLClientAPI_test (
	LoLClientAPI *this
) {

	return true;
}
