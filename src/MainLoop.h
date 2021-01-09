#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// メインループクラス
class MainLoop
{
public:
	/// コンストラクタ
	MainLoop(LPDIRECT3DDEVICE9);
	/// デストラクタ
	~MainLoop();

	/// アプリケーションのメインループ
	bool Loop();

private:
	/// レンダリングデバイス
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	/// 描画
	void Render();

};

} // namespace
