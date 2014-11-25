#include "HookEngine.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HookEngine"
#include "dbg/dbg.h"

/*
 * Description 	: Allocate a new HookEngine structure.
 * char * hookEngineDllPath : DLL path of NtHookEngine.dll
 * Return		: A pointer to an allocated HookEngine.
 */
HookEngine *
HookEngine_new (
	char * hookEngineDllPath
) {
	HookEngine *this;

	if ((this = calloc (1, sizeof(HookEngine))) == NULL)
		return NULL;

	if (!HookEngine_init (this, hookEngineDllPath)) {
		HookEngine_free (this);
		return NULL;
	}

	return this;
}


/*
 * Description : Initialize an allocated HookEngine structure.
 * char * hookEngineDllPath : DLL path of NtHookEngine.dll
 * HookEngine *this : An allocated HookEngine to initialize.
 */
bool
HookEngine_init (
	HookEngine *this,
	char * hookEngineDllPath
) {
	// Load module
	if (!(this->module = LoadLibrary (hookEngineDllPath))) {
		dbg ("LoadLibrary <%s> failed.", hookEngineDllPath);
		return false;
	}

	// Load function from the module
	HookEngine_hook = (typeof(HookEngine_hook))
						GetProcAddress (this->module, "HookFunction");

	HookEngine_unhook = (typeof(HookEngine_unhook))
						GetProcAddress (this->module, "UnhookFunction");

	HookEngine_get_original_function = (typeof(HookEngine_get_original_function))
						GetProcAddress (this->module, "GetOriginalFunction");

	if (!HookEngine_hook || !HookEngine_unhook || !HookEngine_get_original_function) {
		dbg ("Error while loading functions in NtHookEngine.");
		return false;
	}

	dbg ("HookEngine initialized correctly.");

	return true;
}


/*
 * Description : Free an allocated HookEngine structure.
 * HookEngine *this : An allocated HookEngine to free.
 */
void
HookEngine_free (
	HookEngine *this
) {
	if (this != NULL)
	{
		free (this);
	}
}


/*
 * Description : Unit tests checking if a HookEngine is coherent
 * HookEngine *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HookEngine_test (
	HookEngine *this
) {

	return true;
}
