#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
myGame::SystemMain systemMain;
}

//-------------------------------------------------------------------------------------------------
/// エントリー関数
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	if (systemMain.initialize(hInst)) {
		systemMain.msgLoop();
	}

	return 0;
}

// EOF
