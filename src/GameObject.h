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
	GameObject(Transform aTransform);
	GameObject(GameObjectTag aTag);
	GameObject(Transform aTransform, GameObjectTag aTag);
	//@}

	/// @name 外部呼出し用の更新/描画
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

	/// @name アクセサ
	//@{
	const Transform& transform() const;
	const GameObjectTag& tag() const;
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	Transform mTransform;
	GameObjectTag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
