#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
/// ウィンドウプロシージャのプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// システム管理クラス
class SystemMain final
{
public:
	/// コンストラクタ
	SystemMain(HINSTANCE);
	/// デストラクタ
	~SystemMain();

	/// ウィンドウプロシージャ
	LRESULT MyWndProc(HWND, UINT, WPARAM, LPARAM);

	/// 初期化処理
	bool Init();
	/// メッセージループ
	void MsgLoop();


private:
	/// インスタンスハンドル
	HINSTANCE m_hInst;
	/// ウィンドウハンドル
	HWND m_hWnd;

	/// IDirect3D9コンポーネント
	LPDIRECT3D9 m_pD3D;
	/// D3Dデバイスを生成するための構造体
	D3DPRESENT_PARAMETERS m_D3DPParams;
	/// レンダリングデバイス
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	/// ウィンドウ初期化
	HRESULT InitWindow();

	/// Direct3D初期化
	HRESULT	InitDirect3D();
	/// Direct3Dの開放
	void ReleaseDirect3D();

	/// 描画
	void Render();

};

} // namespace
