#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

//-------------------------------------------------------------------------------------------------
/// DirectXオブジェクトの開放マクロ
/// @param aD3DObject 開放するオブジェクト
#define SAFE_RELEASE(aD3DObject) \
    if (aD3DObject) { \
	    aD3DObject->Release(); \
	    aD3DObject = NULL; \
    } 

// EOF
