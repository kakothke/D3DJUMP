#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
MainLoop::MainLoop(LPDIRECT3DDEVICE9 a_pD3DDevice)
	: m_pD3DDevice(a_pD3DDevice)
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
MainLoop::~MainLoop()
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �A�v���P�[�V�����̃��C�����[�v
/// </summary>
/// <returns> false��Ԃ��ƃ��C�����[�v�𔲂��ăA�v���P�[�V�������I������ </returns>
bool MainLoop::Loop()
{
	Render();
	return true;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �`��
/// </summary>
void MainLoop::Render()
{
	// Z�o�b�t�@�ƃo�b�N�o�b�t�@���N���A
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 64), 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene())) {
		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@��\��ʂɕ`��
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

} // namespace
