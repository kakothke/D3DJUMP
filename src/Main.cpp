#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
myGame::SystemMain systemMain;
}

//-------------------------------------------------------------------------------------------------
/// �G���g���[�֐�
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	if (systemMain.initialize(hInst)) {
		systemMain.msgLoop();
	}

	return 0;
}

// EOF
