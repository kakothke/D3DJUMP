#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �e�X�g�p�̃Q�[���I�u�W�F�N�g
class TestPlane : public GameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	TestPlane();
	TestPlane(Transform);
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() const override;
	//@}

};

} // namespace
// EOF
