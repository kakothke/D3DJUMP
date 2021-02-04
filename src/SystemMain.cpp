#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Window.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// ����������
bool SystemMain::initialize(HINSTANCE a_hInst) const
{
	// �E�B���h�E������
	if (!Window::getInst()->initialize(a_hInst)) {
		return false;
	}
	// Direct3D9������
	if (!Direct3D9::getInst()->initialize(Window::getInst()->hWnd())) {
		return false;
	}
	// �E�B���h�E��\��
	ShowWindow(Window::getInst()->hWnd(), SW_SHOW);
	UpdateWindow(Window::getInst()->hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	Game game;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OS����̃��b�Z�[�W���E�B���h�E�v���V�[�W���[�ɓn��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// �Q�[���̃��C�����[�v
			if (!game.mainLoop()) {
				break;
			}
		}
	}
}

} // namespace
// EOF
