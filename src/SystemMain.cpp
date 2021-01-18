#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SystemMain::SystemMain()
	: mWindow()
	, mDirectX9()
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
	// DirectX9������
	if (!mDirectX9.initialize(mWindow.hWnd())) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	MainLoop mainLoop(mDirectX9.device());

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
