// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "BbQueue/BbQueue.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _HudChat
{


	DWORD pThis;

	BbQueue chatMessages;

}	HudChat;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new HudChat structure.
 * DWORD baseAddress : Base address of the module
 * DWORD hudChatInstance : The address of hudChat
 * Return		: A pointer to an allocated HudChat.
 */
HudChat *
HudChat_new (
	DWORD baseAddress,
	DWORD hudChatInstance
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated HudChat structure.
 * HudChat *this : An allocated HudChat to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD hudChatInstance : The address of hudChat
 */
bool
HudChat_init (
	HudChat *this,
	DWORD baseAddress,
	DWORD hudChatInstance
);

/*
 * Description : Unit tests checking if a HudChat is coherent
 * HudChat *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudChat_test (
	HudChat *this
);

/*
 * Description : Function called when a message is received.
 *  It is called before the message is displayed in the chat, so it is possible to modify the chatMsg string
 *	HudChat *_this : An allocated HudChat from the client, not the LoLClientAPI structure
 *	char *chatMsg : A string containing the line of the chat added
 * 	int size : The size of the string
 */
void __thiscall
HudChat_addMessage (
	void *_this,
	char *chatMsg,
	int size
);

// --------- Destructors ----------

/*
 * Description : Free an allocated HudChat structure.
 * HudChat *this : An allocated HudChat to free.
 */
void
HudChat_free (
	HudChat *this
);


