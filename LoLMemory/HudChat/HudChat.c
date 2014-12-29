#include "HudChat.h"
#include "HookEngine/HookEngine.h"
#include "Ztring/Ztring.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HudChat"
#include "dbg/dbg.h"

// Singleton
static HudChat *hudChat = NULL;

/*
 * Description 	: Allocate a new HudChat structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated HudChat.
 */
HudChat *
HudChat_new (
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	HudChat *this;

	if ((this = calloc (1, sizeof(HudChat))) == NULL)
		return NULL;

	if (!HudChat_init (this, baseAddress, sizeOfModule)) {
		HudChat_free (this);
		return NULL;
	}

	hudChat = this;

	return this;
}


/*
 * Description : Initialize an allocated HudChat structure.
 * HudChat *this : An allocated HudChat to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
HudChat_init (
	HudChat *this,
	DWORD baseAddress,
	DWORD sizeOfModule
) {
	bb_queue_init (&this->chatMessages);

	HookEngine_hook ((ULONG_PTR) (baseAddress + 0xA07830), (ULONG_PTR) &HudChat_addMessage);

	return true;
}

/*
 * Description : Function called when a message is received.
 *  It is called before the message is displayed in the chat, so it is possible to modify the chatMsg string
 *	HudChat *this : An allocated HudChat
 *	char *chatMsg : A string containing the line of the chat added
 * 	int size : The size of the string
 */
void __thiscall
HudChat_addMessage (
	void *_this,
	char *chatMsg,
	int size
) {
	void (__thiscall *_HudChat_addMessage) (HudChat *this, char *chatMsg, int size);
	_HudChat_addMessage = (typeof(_HudChat_addMessage)) HookEngine_get_original_function ((ULONG_PTR) HudChat_addMessage);

	bb_queue_add (&hudChat->chatMessages, strdup(chatMsg));

	_HudChat_addMessage (_this, chatMsg, size);
}


/*
 * Description : Free an allocated HudChat structure.
 * HudChat *this : An allocated HudChat to free.
 */
void
HudChat_free (
	HudChat *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a HudChat is coherent
 * HudChat *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HudChat_test (
	HudChat *this
) {

	return true;
}
