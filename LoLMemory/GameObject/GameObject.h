// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _GameObject
{




}	GameObject;



// --------- Allocators ---------

/*
 * Description 	: Allocate a new GameObject structure.
 * Return		: A pointer to an allocated GameObject.
 */
GameObject *
GameObject_new (void);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated GameObject structure.
 * GameObject *this : An allocated GameObject to initialize.
 */
bool
GameObject_init (
	GameObject *this
);

/*
 * Description : Unit tests checking if a GameObject is coherent
 * GameObject *this : The instance to test
 * Return : true on success, false on failure
 */
bool
GameObject_test (
	GameObject *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated GameObject structure.
 * GameObject *this : An allocated GameObject to free.
 */
void
GameObject_free (
	GameObject *this
);


