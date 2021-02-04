#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IOnSceneChangedListener* aImpl) : AbstractScene(aImpl)
{
	Mesh::getInst()->initialize();
	Mesh::getInst()->load(MeshList::TestMan);
	Mesh::getInst()->load(MeshList::TestPlane);

	mTestPlane = TestPlane(Transform(Vector3(-2.0f, 5.0f, 4.0f), Vector3(0.0f, 2.0f, 0), Vector3(0.0f, 2.0f, 0.0f)));
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
	mTestMan.update();
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
