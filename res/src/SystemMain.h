#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�v���V�[�W���̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-------------------------------------------------------------------------------------------------
namespace MyGame {

/// �V�X�e���Ǘ��N���X
class SystemMain final
{
public:
	/// �R���X�g���N�^
	SystemMain(HINSTANCE);
	/// �f�X�g���N�^
	~SystemMain();

	/// �E�B���h�E�v���V�[�W��
	LRESULT MyWndProc(HWND, UINT, WPARAM, LPARAM);

	/// ����������
	bool Init();
	/// ���b�Z�[�W���[�v
	void MsgLoop();


private:
	/// �C���X�^���X�n���h��
	HINSTANCE m_hInst;
	/// �E�B���h�E�n���h��
	HWND m_hWnd;

	/// IDirect3D9�R���|�[�l���g
	LPDIRECT3D9 m_pD3D;
	/// D3D�f�o�C�X�𐶐����邽�߂̍\����
	D3DPRESENT_PARAMETERS m_D3DPParams;
	/// �����_�����O�f�o�C�X
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	/// �E�B���h�E������
	HRESULT InitWindow();

	/// Direct3D������
	HRESULT	InitDirect3D();
	/// Direct3D�̊J��
	void ReleaseDirect3D();

	/// �`��
	void Render();

};

} // namespace
