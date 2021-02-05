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
	bool initialize(const HWND& a_hWnd);
	//@}

	/// @name �`��J�n/�`��I��
	//@{
	bool drawStart();
	void drawEnd();
	//@}

	/// @name �J����
	//@{
	void setUpViewMatrix(D3DXVECTOR3 aCameraPos, D3DXVECTOR3 aLookPos, D3DXVECTOR3 aUpVec);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����f�o�C�X��Ԃ�
	LPDIRECT3DDEVICE9 device() const;
	/// �쐬�����v���[���e�[�V�����p�����[�^��Ԃ�
	const D3DPRESENT_PARAMETERS& params();
	//@}

private:
	/// @name ���������֐�
	//@{
	/// �C���^�[�t�F�[�X�̍쐬
	bool createInterface();
	/// �v���[���e�[�V�����p�����[�^�̃Z�b�g�A�b�v
	bool setupPresentParams();
	/// �f�o�C�X�̍쐬
	bool createDeveice();
	/// �r���[�|�[�g�̃Z�b�g�A�b�v
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
