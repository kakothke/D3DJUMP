#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
// �e�X�g�p
#include "TestMan.h"
#include "Camera.h"
#include "Light.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ���C�����[�v
class MainLoop
{
public:
	/// @name �R���X�g���N�^
	//@{
	MainLoop();
	//@}

	/// @name �Q�[���̃��C�����[�v
	//@{
	bool loop();
	//@}

private:
	/// @name �e�X�g�p	
	//@{
	void update();
	void draw() const;
	TestMan TestMan;
	Camera mCamera;
	Light mLight;
	//@}

};

} // namespace
// EOF
