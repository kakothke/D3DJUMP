#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameObject::GameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTransform 初期位置
GameObject::GameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTag オブジェクトの種類
GameObject::GameObject(GameObjectTag aTag)
	: mTransform()
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTransform 初期位置
/// @param aTag オブジェクトの種類
GameObject::GameObject(Transform aTransform, GameObjectTag aTag)
	: mTransform(aTransform)
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
const Transform& GameObject::transform()
{
	return mTransform;
}

//-------------------------------------------------------------------------------------------------
const GameObjectTag& GameObject::tag()
{
	return mTag;
}

} // namespace
// EOF
