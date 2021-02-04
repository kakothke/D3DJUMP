#include "TestMan.h"

//-------------------------------------------------------------------------------------------------
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestMan::TestMan() : GameObject(GameObjcetTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
TestMan::TestMan(Transform aTransform) : GameObject(aTransform, GameObjcetTag::TestMan)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestMan::update()
{
	mTransform.pos.x += .001f;
	mTransform.rot.x += .001f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestMan::draw() const
{
	Mesh::getInst()->draw(MeshList::TestMan, mTransform);
}

} // namespace
// EOF
