#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �V�X�e���Ǘ��N���X
class SystemMain
{
public:
	/// @name WinMain����Ăяo�����֐�
	//@{
	/// ����������
	bool initialize(HINSTANCE a_hInst) const;
	/// ���b�Z�[�W���[�v
	void msgLoop();
	//@}

};

} // namespace
// EOF
