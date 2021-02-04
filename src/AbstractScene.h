#pragma once

//-------------------------------------------------------------------------------------------------
#include "IOnSceneChangedListener.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// シーンの基本クラス
class AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	AbstractScene(IOnSceneChangedListener* aImpl) : mImplSceneChanged(aImpl) {}
	virtual ~AbstractScene() = default;
	//@}

	// @name 仮想関数
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	/// シーン遷移のインターフェース
	IOnSceneChangedListener* mImplSceneChanged;
	//@}

};

} // namespace
// EOF
