#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera() : GameObject(GameObjectTag::Camera)
, mLookPos()
, mIslook(false)
{
	mTransform.pos = Vector3(0, 0, -10);
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
Camera::Camera(Transform aTransform) : GameObject(aTransform, GameObjectTag::Camera)
, mLookPos()
, mIslook(false)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Camera::update()
{
	setUpViewMatrix();
}

//-------------------------------------------------------------------------------------------------
/// �Z�b�g����
void Camera::setUpViewMatrix()
{
	// �J�����ʒu
	D3DXVECTOR3 cameraPos = Vector3Math::D3DXVECTOR3(mTransform.pos);

	// �����_
	if (!mIslook) {
		mLookPos = mTransform.pos + mTransform.rot;
		mLookPos.z = 1;
		mIslook = false;
	}
	D3DXVECTOR3 lookPos = Vector3Math::D3DXVECTOR3(mLookPos);

	// ������̃x�N�g��
	D3DXVECTOR3 upVec;

	Direct3D9::getInst()->setUpViewMatrix(cameraPos, lookPos, upVec);
}

//-------------------------------------------------------------------------------------------------
/// �w�肵���ʒu������
/// @param aPos �����ʒu
void Camera::lookAt(Vector3 aPos)
{
	mLookPos = aPos;
	mIslook = true;
}

} // namespace
// EOF
