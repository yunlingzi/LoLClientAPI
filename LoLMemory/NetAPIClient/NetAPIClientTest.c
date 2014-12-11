#include "NetAPIClient.h"
#include "LoLServerAPI/LoLServerInterface.h"

#define __DEBUG_OBJECT__ "NetAPIClientTest"
#include "dbg/dbg.h"


/*
 * Description : Unit tests checking if a NetAPIClient is coherent
 * NetAPIClient *this : The instance to test
 * Return : true on success, false on failure
 */
bool
NetAPIClient_test (
	NetAPIClient *this
) {
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	return true;
}
