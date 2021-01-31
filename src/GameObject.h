#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include "Transform.h"
#include "Tag.h"

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
	GameObject(Tag);
	GameObject(Transform, Tag);
	//@}

	/// @name 外部呼出し用の更新/描画
	//@{
	virtual void update() = 0;
	virtual void draw() const = 0;
	//@}

	/// @name アクセサ
	//@{
	const Tag& tag();
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	Transform mTransform;
	Tag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
