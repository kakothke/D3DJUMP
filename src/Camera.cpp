#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera() : GameObject(GameObjectTag::Camera)
, mLookPos()
, mZoom(Define::Zoom)
, mIslookAt(false)
{
	mTransform.pos = Vector3(0, 0, -10);
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
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
/// �X�V
void Camera::update()
{
	setViewMatrix();
}

//-------------------------------------------------------------------------------------------------
/// �Z�b�g����
void Camera::setViewMatrix()
{
	// �J�����ʒu
	D3DXVECTOR3 cameraPos = Vector3Math::D3DXVECTOR3(mTransform.pos);

	// �����_
	if (!mIslookAt) {
		mLookPos = mTransform.rot;
		mIslookAt;
	}
	D3DXVECTOR3 lookPos = Vector3Math::D3DXVECTOR3(mLookPos);

	// ���e
	Direct3D9::getInst()->setViewMatrix(cameraPos, lookPos, mZoom);
}

//-------------------------------------------------------------------------------------------------
/// �w�肵���ʒu������
/// @param aPos �����ʒu
void Camera::lookAt(Vector3 aPos)
{
	mLookPos = aPos;
	mIslookAt = true;
}

} // namespace
// EOF
