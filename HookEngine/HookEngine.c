#include "HookEngine.h"
#include <stdlib.h>

// ---------- Debugging -------------
#define __DEBUG_OBJECT__ "HookEngine"
#include "dbg/dbg.h"


// ---- Global exported functions -----
/*
 * Description : Hook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR OriginalFunction : Pointer to the original function hooked
 * ULONG_PTR NewFunction : Pointer to the new function remplacing the old one
 * Return : true on success, false on failure
 */
bool
(__cdecl * _HookEngine_hook) (
	ULONG_PTR OriginalFunction,
	ULONG_PTR NewFunction
);

/*
 * Description : Unhook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR Function : Pointer to the original function hooked to unhook
 */
void
(__cdecl * _HookEngine_unhook) (
	ULONG_PTR Function
);


/*
 * Description : Retrieve a pointer to the original function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR Function : Pointer to the hooking function
 * Return : ULONG_PTR a pointer to the original function
 */
ULONG_PTR
(__cdecl * _HookEngine_get_original_function) (
	ULONG_PTR Hook
);


// --- Implemented functions

// Singleton
HookEngine *hookEngine = NULL;

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

	hookEngine = this;

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
	_HookEngine_hook = (typeof(_HookEngine_hook))
						GetProcAddress (this->module, "HookFunction");

	_HookEngine_unhook = (typeof(_HookEngine_unhook))
						GetProcAddress (this->module, "UnhookFunction");

	_HookEngine_get_original_function = (typeof(_HookEngine_get_original_function))
						GetProcAddress (this->module, "GetOriginalFunction");


	if (!_HookEngine_hook || !_HookEngine_unhook || !_HookEngine_get_original_function) {
		dbg ("Error while loading functions in NtHookEngine.");
		return false;
	}

	this->hookFunctions = bb_queue_new ();

	dbg ("HookEngine initialized correctly.");

	return true;
}


/*
 * Description : Hook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR originalFunction : Pointer to the original function hooked
 * ULONG_PTR newFunction : Pointer to the new function remplacing the old one
 * Return : true on success, false on failure
 */
bool
HookEngine_hook (
	ULONG_PTR originalFunction,
	ULONG_PTR newFunction
) {
	if (!_HookEngine_hook) {
		dbg ("HookEngine is not initialized correctly");
		return false;
	}

	if (!_HookEngine_hook (originalFunction, newFunction)) {
		dbg ("Failed to hook 0x%08X by 0x%08X", originalFunction, newFunction);
		return false;
	}

	bb_queue_add (hookEngine->hookFunctions, (void *) originalFunction);

	return true;
}

/*
 * Description : Hook a target function
 * HookEngine *this : An allocated HookEngine
 * HMODULE module : Module containing the target function
 * char * functionName : Function name in the module
 * ULONG_PTR NewFunction : Pointer to the new function replacing the old one
 * Return : true on success, false on failure
 */
ULONG_PTR
HookEngine_hook_name (
	HMODULE module,
	char * functionName,
	ULONG_PTR NewFunction
) {
	ULONG_PTR functionPtr = (ULONG_PTR) GetProcAddress (module, functionName);

    if (!functionPtr) {
		dbg ("%s not found in module 0x%08X", functionName, module);
		return 0;
    }

	if (!HookEngine_hook (functionPtr, NewFunction)) {
		dbg ("Failed to hook %s", functionName);
		return 0;
	}

	dbg ("\"%s\" hook successful !", functionName);

	return HookEngine_get_original_function (NewFunction);
}

/*
 * Description : Unhook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR function : Pointer to the original function hooked to unhook
 */
void
HookEngine_unhook (
	ULONG_PTR function
) {
	return _HookEngine_unhook (function);
}


/*
 * Description : Unhook all the registred hooked function
 * Return : void
 */
void
HookEngine_unhook_all (
	void
) {
	while (bb_queue_get_length (hookEngine->hookFunctions)) {
		ULONG_PTR function = (ULONG_PTR) bb_queue_get_first (hookEngine->hookFunctions);
		HookEngine_unhook (function);
	}
}


/*
 * Description : Retrieve a pointer to the original function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR Function : Pointer to the hooking function
 * Return : ULONG_PTR a pointer to the original function
 */
ULONG_PTR
HookEngine_get_original_function (
	ULONG_PTR Hook
) {
	return _HookEngine_get_original_function (Hook);
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
	if (!this) {
		fail ("Instance is NULL");
		return false;
	}

	return true;
}
