#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �Q�[���S��
class Game
{
public:
	/// @name �R���X�g���N�^
	//@{
	Game();
	//@}

	/// @name �Q�[���̃��C�����[�v
	//@{
	bool mainLoop();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���Ǘ�
	SceneManager mSceneManager;
	//@}

};

} // namespace
// EOF
