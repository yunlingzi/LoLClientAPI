// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.30.29
#pragma once

// ---------- Includes ------------
#include "../MemProc/MemProc.h"
#include "LoLMemory/HudManager/HudManager.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _LoLProcess
{
	MemProc *process;

	// Memory structures
	DWORD HudManagerInstanceAddr;
	HudManager *hud;


}	LoLProcess;



// --------- Constructors ---------

LoLProcess *
LoLProcess_new (void);

LoLProcess *
LoLProcess_alloc (void);

// ----------- Functions ------------

void
LoLProcess_init (LoLProcess *LoLProcess);


// --------- Destructors ----------

void
LoLProcess_free (LoLProcess *LoLProcess);


