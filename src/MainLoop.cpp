#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
MainLoop::MainLoop(LPDIRECT3DDEVICE9 a_pD3DDevice)
	: m_pD3DDevice(a_pD3DDevice)
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// デストラクタ
/// </summary>
MainLoop::~MainLoop()
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// アプリケーションのメインループ
/// </summary>
/// <returns> falseを返すとメインループを抜けてアプリケーションが終了する </returns>
bool MainLoop::Loop()
{
	Render();
	return true;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// 描画
/// </summary>
void MainLoop::Render()
{
	// Zバッファとバックバッファをクリア
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 64), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene())) {
		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファを表画面に描画
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

} // namespace
