#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// システム管理クラス
class SystemMain
{
public:
	/// @name WinMainから呼び出される関数
	//@{
	/// 初期化処理
	bool initialize(HINSTANCE) const;
	/// メッセージループ
	void msgLoop();
	//@}

};

} // namespace
// EOF
