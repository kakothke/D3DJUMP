#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �e�X�g�p�̃Q�[���I�u�W�F�N�g
class TestMan : public GameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	TestMan();
	TestMan(Transform aTransform);
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() const override;
	//@}

};

} // namespace
// EOF
