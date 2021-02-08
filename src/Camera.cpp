#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera() : GameObject(GameObjectTag::Camera)
, mLookPos()
, mZoom(Define::Zoom)
, mIslookAt(false)
{
	mTransform.pos = Vector3(0, 0, -10);
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
Camera::Camera(Transform aTransform) : GameObject(aTransform, GameObjectTag::Camera)
, mLookPos()
, mZoom(Define::Zoom)
, mIslookAt(false)
{
}

Camera::Camera(float aZoom) : GameObject(GameObjectTag::Camera)
, mLookPos()
, mZoom(aZoom)
, mIslookAt(false)
{
	mTransform.pos = Vector3(0, 0, -10);
}

Camera::Camera(Transform aTransform, float aZoom) : GameObject(aTransform, GameObjectTag::Camera)
, mLookPos()
, mZoom(aZoom)
, mIslookAt(false)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Camera::update()
{
	setViewMatrix();
}

//-------------------------------------------------------------------------------------------------
/// セットする
void Camera::setViewMatrix()
{
	// カメラ位置
	D3DXVECTOR3 cameraPos = Vector3Math::D3DXVECTOR3(mTransform.pos);

	// 注視点
	if (!mIslookAt) {
		mLookPos = mTransform.rot;
		mIslookAt;
	}
	D3DXVECTOR3 lookPos = Vector3Math::D3DXVECTOR3(mLookPos);

	// 投影
	Direct3D9::getInst()->setViewMatrix(cameraPos, lookPos, mZoom);
}

//-------------------------------------------------------------------------------------------------
/// 指定した位置を向く
/// @param aPos 向く位置
void Camera::lookAt(Vector3 aPos)
{
	mLookPos = aPos;
	mIslookAt = true;
}

} // namespace
// EOF
