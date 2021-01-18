#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ���C�����[�v
class MainLoop
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	MainLoop(LPDIRECT3DDEVICE9);
	~MainLoop();
	//@}

	/// @name �Q�[���̃��C�����[�v
	//@{
	bool loop();
	//@}

private:
	/// @name ��������
	//@{
	/// �`��
	void draw();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �����_�����O�f�o�C�X
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	//@}

};

} // namespace
// EOF
