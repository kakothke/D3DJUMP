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
	Camera(D3DXVECTOR3, D3DXVECTOR3);
	//@}
	
	/// @name �X�V
	//@{
	void update();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	D3DXVECTOR3 mCameraPos;
	D3DXVECTOR3 mLookPos;
	//@}

};

} // namespace
// EOF
