#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Fps.h"
#include "Macros.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�v���V�[�W���̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// �V�X�e���Ǘ��N���X
class SystemMain
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SystemMain(HINSTANCE);
	~SystemMain();
	//@}

	/// @name �E�B���h�E�v���V�[�W��
	//@{
	LRESULT myWndProc(HWND, UINT, WPARAM, LPARAM);
	//@}

	/// @name WinMain����Ăяo�����֐�
	//@{
	/// ����������
	bool initialize();
	/// ���b�Z�[�W���[�v
	void msgLoop();
	//@}

private:
	/// @name ��������
	//@{
	/// ���d�N�����`�F�b�N����
	bool checkMultiple();
	/// �E�B���h�E������������
	bool initializeWindow();
	/// Direct3D������������
	bool initializeDirect3D();
	/// Direct3D���J������
	void releaseDirect3D();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �C���X�^���X�n���h��
	HINSTANCE m_hInst;
	/// �E�B���h�E�n���h��
	HWND m_hWnd;
	/// Mutex
	HANDLE m_hMutex;
	/// IDirect3D9�R���|�[�l���g
	LPDIRECT3D9 m_pD3D;
	/// D3D�f�o�C�X�𐶐����邽�߂̍\����
	D3DPRESENT_PARAMETERS mD3DPParams;
	/// �����_�����O�f�o�C�X
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	/// fps�𐧌䂷��
	Fps mFps;
	//@}

};

} // namespace
// EOF
