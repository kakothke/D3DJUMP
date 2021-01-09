#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// 定数クラス
class Define final
{
public:
    /// ウィンドウサイズ横
    const static INT WindowWidth;
    /// ウィンドウサイズ縦
    const static INT WindowHeight;
    /// ウィンドウ名
    const static LPCWSTR WindowName;
    /// フルスクリーンモードフラグ
    const static BOOL FullScreenMode;

};

} // namespace
