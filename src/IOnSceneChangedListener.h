#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneList.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// シーン遷移のインターフェース
class IOnSceneChangedListener
{
public:
	IOnSceneChangedListener() = default;
	virtual ~IOnSceneChangedListener() = default;
	virtual void onSceneChanged(const SceneList aSceneList) = 0;

};

} // namespace
// EOF
