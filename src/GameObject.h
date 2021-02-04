#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include "Transform.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ゲームオブジェクトの抽象基本クラス
class GameObject
{
public:
	/// @name コンストラクタ
	//@{
	GameObject();
	GameObject(Transform);
	GameObject(GameObjcetTag);
	GameObject(Transform, GameObjcetTag);
	//@}

	/// @name 外部呼出し用の更新/描画
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

	/// @name アクセサ
	//@{
	const GameObjcetTag& tag();
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	Transform mTransform;
	GameObjcetTag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
