// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "dx/d3d9.h"
#include "dx/d3dx9.h"
#include "D3D9Hook/D3D9Hook.h"

// ---------- Defines -------------


// ------ Structure declaration -------
typedef struct _LoLDx
{
	D3D9Hook *d3d9Hook;


}	LoLDx;
extern LoLDx * lolDx;

// --------- Allocators ---------

/*
 * Description 	: Allocate a new LoLDx structure.
 * DWORD baseAddress : Base address of the module
 * DWORD hudChatInstance : The address of hudChat
 * Return		: A pointer to an allocated LoLDx.
 */
LoLDx *
LoLDx_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated LoLDx structure.
 * LoLDx *this : An allocated LoLDx to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD hudChatInstance : The address of hudChat
 */
bool
LoLDx_init (
	LoLDx *this,
	DWORD baseAddress,
	DWORD sizeOfModule
);

/*
 * Description : Unit tests checking if a LoLDx is coherent
 * LoLDx *this : The instance to test
 * Return : true on success, false on failure
 */
bool
LoLDx_test (
	LoLDx *this
);

/// Hooked functions

/*
 * Description : d3d9 EndScene hooked function
 * Return : result of the original function
 */
HRESULT WINAPI
LoLDx_EndScene (
	LPDIRECT3DDEVICE9 pDevice
);

/*
 * Description : d3d9 DrawIndexedPrimitive hooked function.
 * Return : result of the original function
 */
HRESULT WINAPI
LoLDx_DrawIndexedPrimitive (
	LPDIRECT3DDEVICE9 pDevice,
	D3DPRIMITIVETYPE PrimType,
	INT BaseVertexIndex,
	UINT MinVertexIndex,
	UINT NumVertices,
	UINT startIndex,
	UINT primCount
);

/*
 * Description : d3d9 Reset hooked function.
 * Return : result of the original function
 */
HRESULT WINAPI
LoLDx_Reset (
	LPDIRECT3DDEVICE9 pDevice,
	D3DPRESENT_PARAMETERS* pPresentationParameters
);

// --------- Destructors ----------

/*
 * Description : Free an allocated LoLDx structure.
 * LoLDx *this : An allocated LoLDx to free.
 */
void
LoLDx_free (
	LoLDx *this
);


