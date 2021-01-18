#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SystemMain::SystemMain()
	: mWindow()
	, mDirectX9()
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
	// DirectX9初期化
	if (!mDirectX9.initialize(mWindow.hWnd())) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	MainLoop mainLoop(mDirectX9.device());

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
