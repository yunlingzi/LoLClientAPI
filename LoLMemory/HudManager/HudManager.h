// --- Author : Moreau Cyril - Spl3en
// --- Date   : 2014-09-30-20.37.58
#pragma once

// ---------- Includes ------------
#include "LoLClientAPI.h"
#include "Position/Position.h"
#include "MemProc/MemProc.h"

// ---------- Defines -------------

// ------ Structure declaration -------
#pragma pack(push, 1)
typedef struct _HudManager
{
  int field_0;
  int field_1;
  int field_2;
  int field_3;
  int field_4;
  int field_5;
  int field_6;
  int field_7;
  int field_8;
  int field_9;
  int field_10;
  int field_11;
  int field_12;
  int field_13;
  int field_14;
  int field_15;
  int field_16;
  int field_17;
  int field_18;
  int field_19;
  int field_20;
  int field_21;
  int field_22;
  char field_23;
  char field_24;
  short int field_5E;
  char gap_60[164];
  Position cameraPosition;

  DWORD thisAddr;

} HudManager;
#pragma pack(pop)



// --------- Constructors ---------

HudManager *
HudManager_new (MemProc *mp);

HudManager *
HudManager_alloc (void);

// ----------- Functions ------------

bool
HudManager_init (HudManager *HudManager, MemProc *mp);

bool
HudManagerTest (HudManager *hud);

// --------- Destructors ----------

void
HudManager_free (HudManager *HudManager);


