#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ���C�g
class Light : public GameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	Light();
	Light(LPDIRECT3DDEVICE9, Transform);
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() const override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���C�g 
	D3DLIGHT9 mLight;
	//@}

};

} // namespace
// EOF
