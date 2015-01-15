#include "LoLProcess.h"
#include "LoLServerAPI/LoLServerInterface.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define __DEBUG_OBJECT__ "LoLProcess"
#include "dbg/dbg.h"


/*
 * Description 	: Allocate a new LoLProcess structure.
 * Return		: A pointer to an allocated LoLProcess.
 */
LoLProcess *
LoLProcess_new (void)
{
	LoLProcess *this;

	if ((this = calloc (1, sizeof(LoLProcess))) == NULL) {
		return NULL;
	}

	if (!LoLProcess_init (this)) {
		warn ("Initialization failed.");
		LoLProcess_free (this);
		return NULL;
	}

	// Initialization successful :
	// Bind the current LoLProcess to the LoLServerAPI instance
	set_LoLProcess (this);
	LoLProcess_setState (this, STATE_TESTING);

	// Unit testing
	if (!LoLProcess_test (this)) {
		fail ("LoLProcess unit test failed.");
		log_chat_message ("<font color=\"#ff3333\">LoLClientAPI failed to start.</font>", -1);
		LoLProcess_setState (this, STATE_ERROR);
		return NULL;
	}
	else {
		dbg ("[OK] LoLProcess test success.");
	}

	LoLProcess_setState (this, STATE_READY);

	// Send a ready message to the chat log
	log_chat_message ("<font color=\"#33ff33\">LoLClientAPI is ready.</font>", -1);

	return this;
}


/*
 * Description      : Set the LoLprocess to a given state
 * LoLProcess *this : An allocated LoLProcess
 * Return           : void
 */
void
LoLProcess_setState (
	LoLProcess *this,
	LoLProcessState state
) {
	switch (state)
	{
		case STATE_READY:
			dbg ("====== API State : READY! ====== ");
		break;
		case STATE_TESTING:
			dbg ("====== API State : TESTING... ====== ");
		break;
		case STATE_INITIALIZING:
			dbg ("====== API State : INITIALIZING... ====== ");
		break;
		case STATE_ERROR:
			dbg ("====== API State : ERROR! ====== ");
		break;
	}

	this->state = state;
}


/*
 * Description      : Load the Hook Engine into the LoL process
 * LoLProcess *this : An allocated LoLProcess
 * Return           : void
 */
bool
LoLProcess_load_hook_engine (
	LoLProcess *this
) {
	// Load hook engine
	char * hookEngineDllPath = str_dup_printf ("%sbin/NtHookEngine.dll", this->appPath);
	this->hookEngine = HookEngine_new (hookEngineDllPath);
	free (hookEngineDllPath);

	if (!this->hookEngine) {
		fail ("Hook Engine didn't initialize correctly");
		return false;
	}

	return true;
}


/*
 * Description      : Scan different modules of the League of Legends.exe process
 * LoLProcess *this : An allocated LoLProcess
 * Return           : true on success, false otherwise
 */
bool
LoLProcess_scan_modules (
	LoLProcess *this
) {
	// Retrieve modules from PEB
	MODULE_INFORMATION_TABLE * moduleTable = QueryModuleInformationProcess ();

	if (!moduleTable) {
		fail ("Module table not found.");
		return false;
	}

	// Scan modules
	for (unsigned int i = 0; i < moduleTable->ModuleCount; i++)
	{
		MODULE_ENTRY *moduleEntry = &moduleTable->Modules[i];
		DWORD baseAddress  = (DWORD) moduleEntry->BaseAddress;
		DWORD sizeOfModule = (DWORD) moduleEntry->SizeOfImage - 1;

		// RiotLauncher.dll
		if (_wcsicmp (moduleEntry->BaseName.Buffer, L"RiotLauncher.dll") == 0) {
			dbg ("Maestro module found : 0x%08X (size = 0x%08X)", baseAddress, sizeOfModule);
			// if ((this->maestro = Maestro_new (baseAddress, sizeOfModule)) == NULL) {
			// 	warn ("Maestro module not found");
			// 	return false;
			// }
		}

		// d3d9.dll
		else if (_wcsicmp (moduleEntry->BaseName.Buffer, L"d3d9.dll") == 0) {
			// Load DirectX hooks
			dbg ("d3d9 module found : 0x%08X (size = 0x%08X)", baseAddress, sizeOfModule);
			if ((this->dx = LoLDx_new (baseAddress, sizeOfModule)) == NULL) {
				fail ("Error when hooking d3d9 module.");
				return false;
			}
		}

		// League Of Legends.exe
		else if (_wcsicmp (moduleEntry->BaseName.Buffer, L"League of Legends.exe") == 0) {
			dbg ("LoL module found : 0x%08X (size = 0x%08X)", baseAddress, sizeOfModule);
			if ((this->lol = LoLModule_new (baseAddress, sizeOfModule)) == NULL) {
				fail ("LoL base image module not initialized correctly.");
				return false;
			}
		}
	}

	return true;
}

/*
 * Description      :	Initialize an allocated LoLProcess structure.
 *					    Read the game structures
 * LoLProcess *this : An allocated LoLProcess to initialize.
 * Return           : true on success, false on failure.
 */
bool
LoLProcess_init (
	LoLProcess *this
) {
	// Init state
	LoLProcess_setState (this, STATE_INITIALIZING);

	// Get the application path from the module path
	char *serverApiPath = get_module_path ("LoLServerAPI.dll");
	this->appPath = str_dup_printf ("%s../", serverApiPath);
	if (!this->appPath || !strlen (serverApiPath)) {
		MessageBoxA (NULL, "LoLClientAPI cannot initialize correctly", "Error", 0);
		return false;
	}
	free (serverApiPath);

	// Open debug file
	char *logFilePath = str_dup_printf ("%sLoLClientAPI-Log.txt", this->appPath);
	this->debugOutput = file_open (logFilePath, "w+");
	if (this->debugOutput) {
		dbg_set_output (this->debugOutput);
	}
	dbg ("appPath set to <%s>", this->appPath);
	free (logFilePath);

	// Get time and start logging
	struct tm now = *localtime ((time_t[]) {time(NULL)});
	dbg ("====== Injection started at %4d-%02d-%02d %02d:%02d:%02d ======",
		now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);

	// Detect window
	this->hwnd = get_hwnd_from_title ("League of Legends (TM) Client");

	// Load Hook Engine
	if (!LoLProcess_load_hook_engine (this)) {
		fail ("Error when loading NtHookEngine.");
		return false;
	}

	// Detect LoL modules
	if (!LoLProcess_scan_modules (this)) {
		fail ("Error when scanning modules.");
		return false;
	}

	return true;
}


/*
 * Description      : Export current memory addresses to CheatEngine
 * LoLProcess *this : An allocated LoLProcess
 * Return           : void
 */
void
LoLProcess_exportToCE (
	LoLProcess *this
) {
	#ifdef EXPORT_TO_CHEATENGINE
	char * cheatEngineXmlFormat = file_get_contents("C:/Users/Spl3en/Desktop/C/LoLClientAPI/LCAPIFormat.ct");
	if (!cheatEngineXmlFormat) {
		return;
	}

	char * cheatEngineOutput = malloc (strlen(cheatEngineXmlFormat) + 10000);

	sprintf (cheatEngineOutput, cheatEngineXmlFormat,
		/* Camera */
		LoLProcess_get_addr (this->lol->hudManager->hudCamera, cameraPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCamera, cameraPosition),

		/* Cursor */
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, rightClickPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, rightClickPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, EntityFocusedPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, EntityFocusedPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, posRaw),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, posRaw),

		/* Destination */
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, rightClickPosition),
		LoLProcess_get_addr (this->lol->hudManager->hudCursorTarget, rightClickPosition),

		/* HeroClient */
		LoLProcess_get_addr (this->lol->heroClient, summonerName),
		LoLProcess_get_addr (this->lol->heroClient, currentPosition),
		LoLProcess_get_addr (this->lol->heroClient, currentPosition),
		LoLProcess_get_addr (this->lol->heroClient, team),
		LoLProcess_get_addr (this->lol->heroClient, curHP),
		LoLProcess_get_addr (this->lol->heroClient, maxHP),

		/* ChampionArray */
		this->lol->championArray->championsCount,
		LoLProcess_get_addr (this->lol->championArray, start),
		LoLProcess_get_addr (this->lol->championArray, end),

		/* GUIMenu */
			// GUIMinimap
			this->lol->guiMenu->pStaticThis,
			this->lol->guiMenu->pStaticThis
	);

	file_put_contents("C:/Users/Spl3en/Desktop/C/LoLClientAPI/LCAPI.ct", cheatEngineOutput, NULL);
	dbg ("Addresses exported to CheatEngine.");
	#endif
}


/*
 * Description      : Free an allocated LoLProcess structure.
 * LoLProcess *this : An allocated LoLProcess to free.
 */
void
LoLProcess_free (
	LoLProcess *this
) {
	if (this != NULL)
	{
		LoLModule_free (this->lol);

		free (this);
	}
}
