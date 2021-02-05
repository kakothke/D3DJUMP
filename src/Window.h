#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Singleton.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// Window�̊Ǘ�
class Window : public Singleton<Window>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Window();
	~Window();
	//@}

	/// @name ����������
	//@{
	bool initialize(const HINSTANCE& a_hInst);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����E�B���h�E�n���h����Ԃ�
	HWND hWnd() const;
	//@}

private:
	/// @name �������֐�
	//@{
	bool checkMultiple();
	bool registerClass();
	bool createWindow();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// 
	HINSTANCE m_hInst;
	/// �E�B���h�E�n���h��
	HWND m_hWnd;
	/// �~���[�e�b�N�X
	HANDLE m_hMutex;
	//@}

};

} // namespace
// EOF
