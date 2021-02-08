#pragma once
#pragma warning( disable : 4996 )

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include "Singleton.h"
#include <tchar.h>
#include <stdlib.h>
#include <string>

//-------------------------------------------------------------------------------------------------
using namespace std;

//-------------------------------------------------------------------------------------------------
namespace myGame
{

/// Direct3D�p�f�o�b�O�t�H���g�N���X
class DebugFont : public Singleton<DebugFont>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	DebugFont();
	~DebugFont();
	//@}

	/// �`��֐�
	//@{
	/// ������̂ݕ`��
	void draw(const LPCTSTR aString);
	void draw(const LPCTSTR aString, float aX, float aY);
	/// �ϐ����ݕ`��
	/*template <typename... T>
	void draw(LPCTSTR aString, T... a);*/
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �t�H���g�I�u�W�F�N�g�|�C���^
	LPD3DXFONT m_pFont;
	/// �t�H���g����
	D3DXFONT_DESC mD3DFD;
	//@}

};

} // namespace
// EOF
