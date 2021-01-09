#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// ���C�����[�v�N���X
class MainLoop
{
public:
	/// �R���X�g���N�^
	MainLoop(LPDIRECT3DDEVICE9);
	/// �f�X�g���N�^
	~MainLoop();

	/// �A�v���P�[�V�����̃��C�����[�v
	bool Loop();

private:
	/// �����_�����O�f�o�C�X
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	/// �`��
	void Render();

};

} // namespace
