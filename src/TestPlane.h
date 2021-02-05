#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// テスト用のゲームオブジェクト
class TestPlane : public GameObject
{
public:
	/// name コンストラクタ
	//@{
	TestPlane();
	TestPlane(Transform aTransform);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() const override;
	//@}

};

} // namespace
// EOF
