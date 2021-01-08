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
    const static INT Window_Width;
    /// ウィンドウサイズ縦
    const static INT Window_Height;
    /// ウィンドウ名
    const static LPCWSTR Window_Name;

};

} // namespace
