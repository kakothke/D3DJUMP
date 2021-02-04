#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera()
	: mCameraPos(D3DXVECTOR3(0, 0, -10))
	, mLookPos(D3DXVECTOR3(0, 0, 0))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param mCameraPos カメラの位置
/// @param mLookPos 注視点
Camera::Camera(D3DXVECTOR3 aCameraPos, D3DXVECTOR3 aLookPos)
	: mCameraPos(aCameraPos)
	, mLookPos(aLookPos)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Camera::update()
{
	Direct3D9::getInst()->setUpViewMatrix(mCameraPos, mLookPos);
}

} // namespace
// EOF
