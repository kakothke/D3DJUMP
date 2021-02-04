#pragma once

//-------------------------------------------------------------------------------------------------
#include "IOnSceneChangedListener.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �V�[���̊�{�N���X
class AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	AbstractScene(IOnSceneChangedListener* aImpl) : mImplSceneChanged(aImpl) {}
	virtual ~AbstractScene() = default;
	//@}

	// @name ���z�֐�
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

protected:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���J�ڂ̃C���^�[�t�F�[�X
	IOnSceneChangedListener* mImplSceneChanged;
	//@}

};

} // namespace
// EOF
