#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SystemMain::SystemMain()
	: mWindow()
	, mFps()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool SystemMain::initialize(HINSTANCE a_hInst)
{
	// ウィンドウ初期化
	if (!mWindow.initialize(a_hInst)) {
		return false;
	}
	// Direct3D9初期化
	if (!Direct3D9::getInst()->initialize(mWindow.hWnd())) {
		return false;
	}
	// ウィンドウを表示
	ShowWindow(mWindow.hWnd(), SW_SHOW);
	UpdateWindow(mWindow.hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	MainLoop mainLoop;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OSからのメッセージをウィンドウプロシージャーに渡す
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// ゲームのメインループ
			if (!mainLoop.loop()) {
				break;
			}
			// fpsを調整する
			mFps.adjust();
		}
	}
}

} // namespace
// EOF
