#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
MainLoop::MainLoop(LPDIRECT3DDEVICE9 a_pD3DDevice)
	: m_pD3DDevice(a_pD3DDevice)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
MainLoop::~MainLoop()
{
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return false��Ԃ��ƃ��C�����[�v�𔲂��ăA�v���P�[�V�������I������
bool MainLoop::loop()
{
	draw();
	return true;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void MainLoop::draw()
{
	// Z�o�b�t�@�ƃo�b�N�o�b�t�@���N���A
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Define::ClearColor, 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene())) {
		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@��\��ʂɕ`��
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

} // namespace
// EOF
