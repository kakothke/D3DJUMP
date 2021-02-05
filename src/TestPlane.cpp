#include "TestPlane.h"

//-------------------------------------------------------------------------------------------------
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestPlane::TestPlane() : GameObject(GameObjectTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
TestPlane::TestPlane(Transform aTransform) : GameObject(aTransform, GameObjectTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestPlane::update()
{
	//mTransform.pos.x += .002f;
	mTransform.rot.x -= .001f;
	mTransform.rot.y -= .001f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestPlane::draw() const
{
	Mesh::getInst()->draw(MeshList::TestPlane, mTransform);
}

} // namespace
// EOF
