#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SystemMain::SystemMain()
	: mWindow()
	, mFps()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool SystemMain::initialize(HINSTANCE a_hInst)
{
	// �E�B���h�E������
	if (!mWindow.initialize(a_hInst)) {
		return false;
	}
	// Direct3D9������
	if (!Direct3D9::getInst()->initialize(mWindow.hWnd())) {
		return false;
	}
	// �E�B���h�E��\��
	ShowWindow(mWindow.hWnd(), SW_SHOW);
	UpdateWindow(mWindow.hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	MainLoop mainLoop;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OS����̃��b�Z�[�W���E�B���h�E�v���V�[�W���[�ɓn��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// �Q�[���̃��C�����[�v
			if (!mainLoop.loop()) {
				break;
			}
			// fps�𒲐�����
			mFps.adjust();
		}
	}
}

} // namespace
// EOF
