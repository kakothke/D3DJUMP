#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// 定義
class Define
{
public:
    /// @name ウィンドウ設定
    //@{
    /// ウィンドウサイズ横
    const static int WindowWidth = 1280;
    /// ウィンドウサイズ縦
    const static int WindowHeight = 720;
    /// ウィンドウ名
    const static LPCWSTR WindowName;
    //@}

    /// @name DirectX設定
    //@{
    /// フルスクリーン
    const static bool FullScreenMode = false;
    /// 画面クリア色
    const static D3DCOLOR ClearColor;
    //@}

    /// @name ゲーム設定
    //@{
    /// 固定するfps
    const static int Fps = 60;
    //@}

};

} // namespace
// EOF
