#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameObject::GameObject()
	: mTransform()
	, mTag(Tag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTransform 初期位置
GameObject::GameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(Tag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTag オブジェクトの種類
GameObject::GameObject(Tag aTag)
	: mTransform()
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
/// @param aTransform 初期位置
/// @param aTag オブジェクトの種類
GameObject::GameObject(Transform aTransform, Tag aTag)
	: mTransform(aTransform)
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
const Tag& GameObject::tag()
{
	return mTag;
}

} // namespace
// EOF
