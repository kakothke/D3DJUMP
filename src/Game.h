#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "SceneManager.h"
#include "Fps.h"

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
	SceneManager mSceneManager;
	Fps mFps;
	//@}

};

} // namespace
// EOF
