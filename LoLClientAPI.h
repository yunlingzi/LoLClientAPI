#pragma once

#define __out__
#define __in__
#define __opt__
#define __inout__

// Debug
#define __DBG_ACTIVATED__ TRUE

// Dependencies
#include "dbg/dbg.h"



// Exported prototypes
/**
 *	Description : Retrieve the current camera position
 *	__out__ float * x : A pointer to the X position
 *	__out__ float * y : A pointer to the Y position
 */
void
get_camera_position (
	__out__ float * x,
	__out__ float * y
);


/**
 *	Description : Set the current camera position
 *	__in__ float x : New X position
 *	__in__ float y : New Y position
 */
void
set_camera_position (
	__in__ float x,
	__in__ float y
);
