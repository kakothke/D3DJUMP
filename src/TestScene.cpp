#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestScene::TestScene(IOnSceneChangedListener* aImpl) : AbstractScene(aImpl)
{
	Mesh::getInst()->initialize();
	Mesh::getInst()->load(MeshList::TestMan);
	Mesh::getInst()->load(MeshList::TestPlane);

	mTestPlane = TestPlane(Transform(Vector3(-2.0f, 3.0f, 6.0f), Vector3(0.0f, 2.0f, 0), Vector3(0.0f, 2.0f, 0.0f)));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestScene::update()
{
	mCamera.update();

	mLight.update();
	mTestMan.update();
	mTestPlane.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestScene::draw() const
{
	mLight.draw();
	mTestMan.draw();
	mTestPlane.draw();
}

} // namespace
// EOF
