#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "DebugFont.h"
#include <tchar.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IOnSceneChangedListener* aImpl) : AbstractScene(aImpl)
{
	mTestPlane = TestPlane(Transform(Vector3(-2.0f, 3.0f, 6.0f), Vector3(0.0f, 2.0f, 0), Vector3(2.0f, 1.0f, 1.0f)));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestScene::update()
{
	mCamera.update();

	mLight.update();
	//mTestMan.update();
	mTestPlane.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestScene::draw() const
{
	mLight.draw();
	mTestMan.draw();
	mTestPlane.draw();
}

} // namespace
// EOF
