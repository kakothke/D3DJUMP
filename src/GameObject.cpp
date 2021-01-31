#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameObject::GameObject()
	: mTransform()
	, mTag(Tag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTransform �����ʒu
GameObject::GameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(Tag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTag �I�u�W�F�N�g�̎��
GameObject::GameObject(Tag aTag)
	: mTransform()
	, mTag(aTag)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
/// @param aTransform �����ʒu
/// @param aTag �I�u�W�F�N�g�̎��
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
