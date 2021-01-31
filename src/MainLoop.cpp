#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Define.h"
#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
MainLoop::MainLoop()
{
	Mesh::getInst()->initialize();
	Mesh::getInst()->load(MeshList::TestMan);
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return false��Ԃ��ƃ��C�����[�v�𔲂��ăA�v���P�[�V�������I������
bool MainLoop::loop()
{
	update();
	draw();
	return true;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void MainLoop::update()
{
	mCamera.SetupWorldMatrix();
	mLight.update();
	TestMan.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void MainLoop::draw() const
{
	// Z�o�b�t�@�ƃo�b�N�o�b�t�@���N���A
	Direct3D9::getInst()->device()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Define::ClearColor, 1.0f, 0);

	// �`��J�n
	if (SUCCEEDED(Direct3D9::getInst()->device()->BeginScene())) {
		// �e�X�g���b�V����`��
		mLight.draw();
		TestMan.draw();

		// �`��I��
		Direct3D9::getInst()->device()->EndScene();
	}

	// �o�b�N�o�b�t�@��\��ʂɕ`��
	Direct3D9::getInst()->device()->Present(NULL, NULL, NULL, NULL);
}

} // namespace
// EOF
