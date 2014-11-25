// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _HookEngine
{
	HMODULE module;

}	HookEngine;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new HookEngine structure.
 * char * hookEngineDllPath : DLL path of NtHookEngine.dll
 * Return		: A pointer to an allocated HookEngine.
 */
HookEngine *
HookEngine_new (
	char * hookEngineDllPath
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated HookEngine structure.
 * char * hookEngineDllPath : DLL path of NtHookEngine.dll
 * HookEngine *this : An allocated HookEngine to initialize.
 */
bool
HookEngine_init (
	HookEngine *this,
	char * hookEngineDllPath
);

/*
 * Description : Unit tests checking if a HookEngine is coherent
 * HookEngine *this : The instance to test
 * Return : true on success, false on failure
 */
bool
HookEngine_test (
	HookEngine *this
);

/*
 * Description : Hook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR OriginalFunction : Pointer to the original function hooked
 * ULONG_PTR NewFunction : Pointer to the new function remplacing the old one
 * Return : true on success, false on failure
 */
bool
(__cdecl * HookEngine_hook) (
	ULONG_PTR OriginalFunction,
	ULONG_PTR NewFunction
);

/*
 * Description : Unhook a target function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR Function : Pointer to the original function hooked to unhook
 */
void
(__cdecl * HookEngine_unhook) (
	ULONG_PTR Function
);


/*
 * Description : Retrieve a pointer to the original function
 * HookEngine *this : An allocated HookEngine
 * ULONG_PTR Function : Pointer to the hooking function
 * Return : ULONG_PTR a pointer to the original function
 */
ULONG_PTR
(__cdecl * HookEngine_get_original_function) (
	ULONG_PTR Hook
);


// --------- Destructors ----------

/*
 * Description : Free an allocated HookEngine structure.
 * HookEngine *this : An allocated HookEngine to free.
 */
void
HookEngine_free (
	HookEngine *this
);


