#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// テスト用のゲームオブジェクト
class TestMan : public GameObject
{
public:
	/// name コンストラクタ
	//@{
	TestMan();
	TestMan(Transform);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() const override;
	//@}

};

} // namespace
// EOF
