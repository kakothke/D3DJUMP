#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

//-------------------------------------------------------------------------------------------------
/// DirectX�I�u�W�F�N�g�̊J���}�N��
/// @param aD3DObject �J������I�u�W�F�N�g
#define SAFE_RELEASE(aD3DObject) \
    if (aD3DObject) { \
	    aD3DObject->Release(); \
	    aD3DObject = NULL; \
    } 

// EOF
