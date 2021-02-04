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
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	TestScene(IOnSceneChangedListener* aImpl);
	virtual ~TestScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() const override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	Camera mCamera;
	Light mLight;

	TestMan mTestMan;
	TestPlane mTestPlane;
	//@}

};

} // namespace
// EOF
