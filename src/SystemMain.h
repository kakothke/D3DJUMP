#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "DirectX9.h"
#include "Window.h"
#include "Fps.h"
#include "Macros.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �V�X�e���Ǘ��N���X
class SystemMain
{
public:
	/// @name �R���X�g���N�^
	//@{
	SystemMain();
	//@}

	/// @name WinMain����Ăяo�����֐�
	//@{
	/// ����������
	bool initialize(HINSTANCE);
	/// ���b�Z�[�W���[�v
	void msgLoop();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// Window���Ǘ�����
	Window mWindow;
	/// DirectX9���Ǘ�����
	DirectX9 mDirectX9;
	/// fps�𐧌䂷��
	Fps mFps;
	//@}

};

} // namespace
// EOF
