#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
using namespace MyGame;

//-------------------------------------------------------------------------------------------------
/// �O���[�o���ϐ�
SystemMain* systemMain;

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �A�v���P�[�V�����̃G���g���[�֐�
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
/// OS���猩���E�B���h�E�v���V�[�W���[�i���ۂ̏�����SystemMain�N���X��MyWndProc�ŏ����j
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return systemMain->MyWndProc(hWnd, uMsg, wParam, lParam);
}
