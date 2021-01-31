#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ライト
class Light : public GameObject
{
public:
	/// name コンストラクタ
	//@{
	Light();
	Light(LPDIRECT3DDEVICE9, Transform);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() const override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// ライト 
	D3DLIGHT9 mLight;
	//@}

};

} // namespace
// EOF
