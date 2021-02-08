#include "DebugFont.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Macros.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DebugFont::DebugFont()
	: m_pFont(NULL)
	, mD3DFD()
{
	// �f�t�H���g�t�H���g�쐬
	Direct3D9::getInst()->device()->AddRef();
	mD3DFD.Height = 14;
	mD3DFD.Width = 7;
	mD3DFD.Weight = 500;
	mD3DFD.MipLevels = D3DX_DEFAULT;
	mD3DFD.Italic = false;
	mD3DFD.CharSet = DEFAULT_CHARSET;
	mD3DFD.OutputPrecision = OUT_DEFAULT_PRECIS;
	mD3DFD.Quality = DEFAULT_QUALITY;
	mD3DFD.PitchAndFamily = FIXED_PITCH | FF_MODERN;
	memset(mD3DFD.FaceName, 0, sizeof(mD3DFD.FaceName));

	D3DXCreateFontIndirect(Direct3D9::getInst()->device(), &mD3DFD, &m_pFont);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
DebugFont::~DebugFont()
{
	SAFE_RELEASE(m_pFont);
}

//-------------------------------------------------------------------------------------------------
/// �������`��
/// @param aString �`�悷�镶����
void DebugFont::draw(const LPCTSTR aString)
{
	RECT rect;
	SetRect(&rect, 0, 0, 0, 0);
	m_pFont->DrawText(NULL, aString, -1, &rect, DT_LEFT | DT_CALCRECT, 0xffffffff);
	OffsetRect(&rect, 0 * mD3DFD.Width, 0 * mD3DFD.Height);
	m_pFont->DrawText(NULL, aString, -1, &rect, DT_LEFT, 0xffffffff);
}

//-------------------------------------------------------------------------------------------------
/// �������`��
/// @param aString �`�悷�镶����
void DebugFont::draw(const LPCTSTR aString, float aX, float aY)
{
	RECT rect;
	SetRect(&rect, 0, 0, 0, 0);
	m_pFont->DrawText(NULL, aString, -1, &rect, DT_LEFT | DT_CALCRECT, 0xffffffff);
	OffsetRect(&rect, aX * mD3DFD.Width, aY * mD3DFD.Height);
	m_pFont->DrawText(NULL, aString, -1, &rect, DT_LEFT, 0xffffffff);
}

//-------------------------------------------------------------------------------------------------
//void DebugFont::draw(LPCSTR aString, T... a)
//{
//
//}

} // namespace
// EOF
