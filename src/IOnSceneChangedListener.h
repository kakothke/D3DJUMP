#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneList.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �V�[���J�ڂ̃C���^�[�t�F�[�X
class IOnSceneChangedListener
{
public:
	IOnSceneChangedListener() = default;
	virtual ~IOnSceneChangedListener() = default;
	virtual void onSceneChanged(const SceneList aSceneList) = 0;

};

} // namespace
// EOF
