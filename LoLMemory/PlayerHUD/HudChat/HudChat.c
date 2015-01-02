#include "HudChat.h"
#include "HookEngine/HookEngine.h"
#include "Scanner/Scanner.h"
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
 * DWORD hudChatInstance : The address of hudChat
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated HudChat.
 */
HudChat *
HudChat_new (
	DWORD baseAddress,
	DWORD sizeOfModule,
	DWORD hudChatInstance
) {
	HudChat *this;

	if ((this = calloc (1, sizeof(HudChat))) == NULL)
		return NULL;

	if (!HudChat_init (this, baseAddress, sizeOfModule, hudChatInstance)) {
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
 * DWORD hudChatInstance : The address of hudChat
 * DWORD sizeOfModule : Size of the module
 * Return : true on success, false on failure.
 */
bool
HudChat_init (
	HudChat *this,
	DWORD baseAddress,
	DWORD sizeOfModule,
	DWORD hudChatInstance
) {

	this->pThis = hudChatInstance;

	DWORD MaxChatBufferSizeStr = memscan_string (
		"MaxChatBufferSizeStr",
		baseAddress, sizeOfModule,
		"MaxChatBufferSize"
	);

	unsigned char pattern [] = {
	/*
		68 58DE5401   push offset 0154DE58   ; ASCII "MaxChatBufferSize"
		68 C4555E01   push offset 015E55C4   ; ASCII "Hacks"
		68 B4685D01   push offset 015D68B4   ; ASCII "Data/CFG/defaults/GamePermanent.cfg"
	*/
		0x68, '_', '_', '_', '_',
		0x68, '?', '?', '?', '?',
		0x68, '?', '?', '?', '?'
	};

	int replacePos = str_n_pos (pattern, "____", sizeof(pattern));
	memcpy(&pattern[replacePos], &MaxChatBufferSizeStr, 4);

	// Find a reference to addMessageReference
	DWORD addMessageReference = memscan_buffer_mask ("addMessageReference",
		baseAddress, sizeOfModule,
		pattern,
		sizeof (pattern),
		"xxxxx"
		"x????"
		"x????"
	);
	dbg ("addMessageReference found : 0x%08X.", addMessageReference);

	unsigned char startOfFunction [] = {
		0xCC, 0xCC, 0xCC, 0xCC, 0xCC
	};

	int offset = 0;
	while (find_pattern ((char *) addMessageReference - offset, sizeof(startOfFunction), startOfFunction, "xxxxx") == -1) {
		offset++;
		if (offset > 0x1000) {
			warn ("Start of function is really too far. Something must be wrong.");
			return false;
		}
	}

	addMessageReference += sizeof(startOfFunction) - offset;
	dbg ("HudChat_addMessage found : %x", addMessageReference);

	// Init queue messages for client
	bb_queue_init (&this->chatMessages);

	// Hook HudChat_addMessage
	HookEngine_hook ((ULONG_PTR) addMessageReference, (ULONG_PTR) &HudChat_addMessage);

	return true;
}

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
) {
	void (__thiscall *_HudChat_addMessage) (HudChat *this, char *chatMsg, int size)
		= (typeof(_HudChat_addMessage)) HookEngine_get_original_function ((ULONG_PTR) HudChat_addMessage);

	bb_queue_add (&hudChat->chatMessages, strdup (chatMsg));

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
