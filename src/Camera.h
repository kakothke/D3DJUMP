#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �J����
class Camera
{
public:
	/// @name �R���X�g���N�^
	//@{
	Camera();
	//@}

	/// @name �ݒ�
	//@{
	void SetupWorldMatrix();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �J�����̈ʒu
	D3DXVECTOR3 mEye;
	/// �����_
	D3DXVECTOR3 mLookAt;
	/// �J�����̏����
	D3DXVECTOR3 mUpVec;
	//@}

};

} // namespace
// EOF
