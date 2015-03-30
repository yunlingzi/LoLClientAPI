// --- Author       : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "Position/Position.h"
#include <windows.h>
#include <stddef.h>

// ---------- Defines -------------


// ------ Structure declaration -------

#pragma pack(push, 1)
typedef struct _HudCameraZoom
{
	int field_0;
	int field_1;
	int field_2;
	float deltaValue;
	float curValue;
	float targetValue;
	int field_3;

	DWORD pThis;

} HudCameraZoom;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _HudCameraAngle
{
	float y;
	float x;
} HudCameraAngle;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _HudCamera
{
	char field_0[288];
	Position cameraPosition;
	char gap_110[16];
	HudCameraAngle cameraAngle;
	char gap_128[80];
	HudCameraZoom cameraZoom;

	DWORD pThis;

} HudCamera;
#pragma pack(pop)



// --------- Allocators ---------

/*
 * Description 	    : Allocate a new HudCamera structure.
 * DWORD pHudCamera : Address of HudCamera in the target process
 * Return		         : A pointer to an allocated HudCamera.
 */
HudCamera *
HudCamera_new (
	DWORD pHudCamera
);

// ----------- Functions ------------

/*
 * Description      : Initialize an allocated HudCamera structure.
 * HudCamera *this  : An allocated HudCamera to initialize.
 * DWORD pHudCamera : Address of HudCamera in the target process
 * Return           : true on success, false on failure.
 */
bool
HudCamera_init (
	HudCamera *this,
	DWORD pHudCamera
);

/*
 * Description      : Unit tests checking if a HudCamera is coherent
 * Return           : true on success, false on failure
 */
bool
HudCamera_test (
	HudCamera *this
);

// --------- Destructors ----------

/*
 * Description      : Free an allocated HudCamera structure.
 * HudCamera *this  : An allocated HudCamera to free.
 */
void
HudCamera_free (
	HudCamera *this
);


