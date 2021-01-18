#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
MyGame::SystemMain* systemMain = NULL;
}

//-------------------------------------------------------------------------------------------------
/// エントリー関数
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	systemMain = new MyGame::SystemMain(hInst);

	if (systemMain->initialize()) {
		systemMain->msgLoop();
	}
	delete systemMain;

	return 0;
}

//-------------------------------------------------------------------------------------------------
/// OSから見たウィンドウプロシージャー
/// @detail 実際の処理はSystemMainクラスのMyWndProcで行う
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return systemMain->myWndProc(hWnd, uMsg, wParam, lParam);
}

// EOF
