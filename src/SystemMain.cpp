#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Window.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool SystemMain::initialize(HINSTANCE a_hInst) const
{
	// ウィンドウ初期化
	if (!Window::getInst()->initialize(a_hInst)) {
		return false;
	}
	// Direct3D9初期化
	if (!Direct3D9::getInst()->initialize(Window::getInst()->hWnd())) {
		return false;
	}
	// ウィンドウを表示
	ShowWindow(Window::getInst()->hWnd(), SW_SHOW);
	UpdateWindow(Window::getInst()->hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	Game game;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OSからのメッセージをウィンドウプロシージャーに渡す
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// ゲームのメインループ
			if (!game.mainLoop()) {
				break;
			}
		}
	}
}

} // namespace
// EOF
