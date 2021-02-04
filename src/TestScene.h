#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Camera.h"
#include "TestMan.h"
#include "Camera.h"
#include "Light.h"
#include "TestPlane.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

class TestScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	TestScene(IOnSceneChangedListener* aImpl);
	virtual ~TestScene();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() const override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Camera mCamera;
	Light mLight;

	TestMan mTestMan;
	TestPlane mTestPlane;
	//@}

};

} // namespace
// EOF
