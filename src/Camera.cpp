#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera() : GameObject(GameObjectTag::Camera)
, mLookPos()
, mIslook(false)
{
	mTransform.pos = Vector3(0, 0, -10);
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
Camera::Camera(Transform aTransform) : GameObject(aTransform, GameObjectTag::Camera)
, mLookPos()
, mIslook(false)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Camera::update()
{
	setUpViewMatrix();
}

//-------------------------------------------------------------------------------------------------
/// セットする
void Camera::setUpViewMatrix()
{
	// カメラ位置
	D3DXVECTOR3 cameraPos = Vector3Math::D3DXVECTOR3(mTransform.pos);

	// 注視点
	if (!mIslook) {
		mLookPos = mTransform.pos + mTransform.rot;
		mLookPos.z = 1;
		mIslook = false;
	}
	D3DXVECTOR3 lookPos = Vector3Math::D3DXVECTOR3(mLookPos);

	// 上方向のベクトル
	D3DXVECTOR3 upVec;

	Direct3D9::getInst()->setUpViewMatrix(cameraPos, lookPos, upVec);
}

//-------------------------------------------------------------------------------------------------
/// 指定した位置を向く
/// @param aPos 向く位置
void Camera::lookAt(Vector3 aPos)
{
	mLookPos = aPos;
	mIslook = true;
}

} // namespace
// EOF
