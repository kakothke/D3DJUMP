#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameObject::GameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTransform �����ʒu
GameObject::GameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTag �I�u�W�F�N�g�̎��
GameObject::GameObject(GameObjectTag aTag)
	: mTransform()
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTransform �����ʒu
/// @param aTag �I�u�W�F�N�g�̎��
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
