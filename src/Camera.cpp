#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Camera::Camera()
{
	mEye = D3DXVECTOR3(0, 20, 0);
	mLookAt = D3DXVECTOR3(0, 0, 0);
	mUpVec = D3DXVECTOR3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// �J�����̐ݒ�
void Camera::SetupWorldMatrix()
{
	// ���E
	D3DXMATRIXA16 matView;

	D3DXMatrixLookAtLH(&matView, &mEye, &mLookAt, &mUpVec);

	// ���e�s���ݒ�B
	// ����p�A�A�X�y�N�g��A���o�N���b�s���O�p�̍Őڋߋ����ƍŉ��������̎l���K�v�B
	D3DXMATRIXA16 matProj;

	FLOAT tmpAspect = (float)Direct3D9::getInst()->params().BackBufferWidth / (float)Direct3D9::getInst()->params().BackBufferHeight;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		// ����p
		D3DX_PI / 4,
		// �A�X�y�N�g��
		tmpAspect,
		// �ŋߐڋ���
		1.0f,
		// �ŉ�������
		800.0f
	);

	// �r���[�}�g���N�X�̐ݒ�
	Direct3D9::getInst()->device()->SetTransform(D3DTS_VIEW, &matView);

	//�f�B�o�C�X�ɑ΂��āA���e�s���ݒ�B
	Direct3D9::getInst()->device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

} // namespace
// EOF
