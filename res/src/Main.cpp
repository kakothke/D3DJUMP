#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
using namespace MyGame;

//-------------------------------------------------------------------------------------------------
/// グローバル変数
SystemMain* systemMain;

//-------------------------------------------------------------------------------------------------
/// <summary>
/// アプリケーションのエントリー関数
/// </summary>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	systemMain = new SystemMain(hInst);

	if (systemMain->Init()) {
		systemMain->MsgLoop();
	}
	delete systemMain;

	return 0;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// OSから見たウィンドウプロシージャー（実際の処理はSystemMainクラスのMyWndProcで処理）
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return systemMain->MyWndProc(hWnd, uMsg, wParam, lParam);
}
