#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include "Transform.h"
#include "Tag.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �Q�[���I�u�W�F�N�g�̒��ۊ�{�N���X
class GameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	GameObject();
	GameObject(Transform);
	GameObject(Tag);
	GameObject(Transform, Tag);
	//@}

	/// @name �O���ďo���p�̍X�V/�`��
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

	/// @name �A�N�Z�T
	//@{
	const Tag& tag();
	//@}

protected:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Transform mTransform;
	Tag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
