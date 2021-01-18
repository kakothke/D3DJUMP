#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Fps.h"
#include "Macros.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
/// ウィンドウプロシージャのプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// システム管理クラス
class SystemMain
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SystemMain(HINSTANCE);
	~SystemMain();
	//@}

	/// @name ウィンドウプロシージャ
	//@{
	LRESULT myWndProc(HWND, UINT, WPARAM, LPARAM);
	//@}

	/// @name WinMainから呼び出される関数
	//@{
	/// 初期化処理
	bool initialize();
	/// メッセージループ
	void msgLoop();
	//@}

private:
	/// @name 内部実装
	//@{
	/// 多重起動をチェックする
	bool checkMultiple();
	/// ウィンドウを初期化する
	bool initializeWindow();
	/// Direct3Dを初期化する
	bool initializeDirect3D();
	/// Direct3Dを開放する
	void releaseDirect3D();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// インスタンスハンドル
	HINSTANCE m_hInst;
	/// ウィンドウハンドル
	HWND m_hWnd;
	/// Mutex
	HANDLE m_hMutex;
	/// IDirect3D9コンポーネント
	LPDIRECT3D9 m_pD3D;
	/// D3Dデバイスを生成するための構造体
	D3DPRESENT_PARAMETERS mD3DPParams;
	/// レンダリングデバイス
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	/// fpsを制御する
	Fps mFps;
	//@}

};

} // namespace
// EOF
