#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "DirectX9.h"
#include "Window.h"
#include "Fps.h"
#include "Macros.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// システム管理クラス
class SystemMain
{
public:
	/// @name コンストラクタ
	//@{
	SystemMain();
	//@}

	/// @name WinMainから呼び出される関数
	//@{
	/// 初期化処理
	bool initialize(HINSTANCE);
	/// メッセージループ
	void msgLoop();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// Windowを管理する
	Window mWindow;
	/// DirectX9を管理する
	DirectX9 mDirectX9;
	/// fpsを制御する
	Fps mFps;
	//@}

};

} // namespace
// EOF
