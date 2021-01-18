#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// Windowの管理
class Window
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Window();
	~Window();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize(HINSTANCE);
	//@}

	/// @name アクセサ
	//@{
	/// 作成したウィンドウハンドルを返す
	HWND hWnd() const;
	//@}

private:
	/// @name 初期化関数
	//@{
	bool checkMultiple();
	bool registerClass();
	bool createWindow();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// 
	HINSTANCE m_hInst;
	/// ウィンドウハンドル
	HWND m_hWnd;
	/// ミューテックス
	HANDLE m_hMutex;
	//@}

};

} // namespace
// EOF
