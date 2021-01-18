#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// メインループ
class MainLoop
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	MainLoop(LPDIRECT3DDEVICE9);
	~MainLoop();
	//@}

	/// @name ゲームのメインループ
	//@{
	bool loop();
	//@}

private:
	/// @name 内部実装
	//@{
	/// 描画
	void draw();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// レンダリングデバイス
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	//@}

};

} // namespace
// EOF
