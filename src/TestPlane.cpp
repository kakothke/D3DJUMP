#include "TestPlane.h"

//-------------------------------------------------------------------------------------------------
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestPlane::TestPlane() : GameObject(GameObjcetTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
TestPlane::TestPlane(Transform aTransform) : GameObject(aTransform, GameObjcetTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestPlane::update()
{
	mTransform.pos.x += .002f;
	mTransform.rot.x -= .001f;
	mTransform.rot.y -= .001f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestPlane::draw() const
{
	Mesh::getInst()->draw(MeshList::TestPlane, mTransform);
}

} // namespace
// EOF
