#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "Macros.h"
#include "Define.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// Direct3D9�̊Ǘ�
class Direct3D9 : public Singleton<Direct3D9>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Direct3D9();
	~Direct3D9();
	//@}

	/// @name ����������
	//@{
	bool initialize(const HWND&);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����f�o�C�X��Ԃ�
	LPDIRECT3DDEVICE9 device() const;
	/// �쐬�����v���[���e�[�V�����p�����[�^��Ԃ�
	const D3DPRESENT_PARAMETERS& params();
	//@}

private:
	/// @name ��������
	//@{
	/// �C���^�[�t�F�[�X�̍쐬
	bool createInterface();
	/// �v���[���e�[�V�����p�����[�^�̐ݒ�
	bool setupPresentParams();
	/// �f�o�C�X�̍쐬
	bool createDeveice();
	/// �r���[�|�[�g�̐ݒ�
	bool setupViewPort();
	/// �t�H���g�f�o�C�X�̍쐬
	bool createFontDevice();
	/// �܂�����������Ă��Ȃ������̐ݒ�
	bool setupEtc();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �C���^�[�t�F�[�X
	LPDIRECT3D9 mD3DInterface;
	/// �����_�����O�f�o�C�X
	LPDIRECT3DDEVICE9 mD3DDevice;
	/// �E�B���h�E�n���h��
	HWND m_hWnd;
	/// �v���[���e�[�V�����p�����[�^
	D3DPRESENT_PARAMETERS mParams;
	//@}

};

} // namespace
// EOF
