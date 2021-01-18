#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "Macros.h"
#include "Define.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// DirectX9�̊Ǘ�
class DirectX9
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	DirectX9();
	~DirectX9();
	//@}

	/// @name ����������
	//@{
	bool initialize(HWND);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����f�o�C�X��Ԃ�
	LPDIRECT3DDEVICE9 device() const;
	//@}

private:
	/// @name ��������
	//@{
	/// �C���^�[�t�F�[�X�̍쐬
	bool createInterface();
	/// �v���[���e�[�V�����p�����[�^�[�̐ݒ�
	bool setupPresentParams(D3DPRESENT_PARAMETERS&, HWND);
	/// �f�o�C�X�̍쐬
	bool createDeveice(D3DPRESENT_PARAMETERS&, HWND);
	/// �r���[�|�[�g�̐ݒ�
	bool setupViewPort(D3DPRESENT_PARAMETERS&);
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
	//@}

};

} // namespace
// EOF
