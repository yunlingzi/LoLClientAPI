#include "LoLClientAPI.h"
#include "LoLClientInterface.h"
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

	set_api (this);

	return this;
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
	this->closed = true;

	// Initiate the connection
	this->clientSocket = es_client_new_from_ip ("127.0.0.1", LOLAPI_PORT);
	if (this->clientSocket == ES_ERROR_MALLOC || this->clientSocket == ES_ERROR_CONNECT) {
		warn ("LoLServerAPI not found.");
		return false;
	}
	this->closed = true;

	// Receive status
	int answerSize;
	unsigned char * answer = es_recv (this->clientSocket, &answerSize);

	if (answerSize <= 0 || strcmp (answer, LOLAPI_STATUS_READY)) {
		warn ("Malformed LoLAPIServer response.");
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
		if (!this->closed) {
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
