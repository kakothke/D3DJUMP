#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
MyGame::SystemMain* systemMain = NULL;
}

//-------------------------------------------------------------------------------------------------
/// �G���g���[�֐�
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
/// OS���猩���E�B���h�E�v���V�[�W���[
/// @detail ���ۂ̏�����SystemMain�N���X��MyWndProc�ōs��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return systemMain->myWndProc(hWnd, uMsg, wParam, lParam);
}

// EOF
