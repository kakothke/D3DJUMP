#pragma once
#pragma warning( disable : 4996 )

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include <tchar.h>
#include <stdlib.h>
#include <string>

//-------------------------------------------------------------------------------------------------
using namespace std;

//-------------------------------------------------------------------------------------------------
namespace myGame
{

/// DebugFont�p�t���O
enum _DFP_
{
	/// �`��w���t���O
	DF_draw
};

/// Direct3D�p�f�o�b�O�t�H���g�N���X
class DebugFont
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	DebugFont();
	~DebugFont();
	//@}

	/// @name ���Z�q�I�[�o�[���[�h
	//@{
	DebugFont& operator <<(const TCHAR* c);
	DebugFont& operator <<(unsigned char mVal);
	DebugFont& operator <<(short val);
	DebugFont& operator <<(unsigned short val);
	DebugFont& operator <<(int val);
	DebugFont& operator <<(unsigned int val);
	DebugFont& operator <<(float val);
	DebugFont& operator <<(double val);
	DebugFont& operator <<(bool val);
	DebugFont& operator <<(void* ptr);
	DebugFont& operator <<(_DFP_ param);
	/// �ʒu�ݒ�ȈՎw��p���Z�q
	DebugFont& operator ()(int x, int y);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �t�H���g�I�u�W�F�N�g�|�C���^
	ID3DXFont* m_pFont;
	/// �t�H���g����
	D3DXFONT_DESC mD3DFD;
	/// �����p�o�b�t�@
	static TCHAR c[24];
	/// �\���ʒux
	int mX;
	/// �\���ʒuy
	int mY;
#if _UNICODE
	/// �f�o�b�O������ێ��o�b�t�@�iUNICODE�p�j
	wstring mStr;
#else
	/// �f�o�b�O������ێ��o�b�t�@�iANCI�p�j
	string mStr;
#endif
	//@}

};

} // namespace
// EOF
