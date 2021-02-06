#include "DebugFont.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"
#include "Macros.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DebugFont::DebugFont()
	: m_pFont(NULL)
	, mX(0)
	, mY(0)
{
	if (Direct3D9::getInst()->device()) {
		// デフォルトフォント作成
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
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
DebugFont::~DebugFont()
{
	SAFE_RELEASE(m_pFont);
}

//-------------------------------------------------------------------------------------------------
DebugFont& DebugFont::operator <<(const TCHAR* c)
{
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(unsigned char mValue)
{
	_stprintf(c, _T("%d"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(short mValue)
{
	_stprintf(c, _T("%d"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(unsigned short mValue)
{
	_stprintf(c, _T("%d"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(int mValue)
{
	_stprintf(c, _T("%d"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(unsigned int mValue)
{
	_stprintf(c, _T("%d"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(float mValue)
{
	_stprintf(c, _T("%8.3f"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(double mValue)
{
	_stprintf(c, _T("%8.3lf"), mValue);
	mStr += c;
	return *this;
}
DebugFont& DebugFont::operator <<(bool mValue)
{
	if (mValue) {
		mStr += _T("true");
	} else {
		mStr += _T("false");
		return *this;
	}
}
DebugFont& DebugFont::operator <<(void* mPtr)
{
	_stprintf(c, _T("%08x"), mPtr);
	mStr += c;
	return *this;
}

//-------------------------------------------------------------------------------------------------
DebugFont& DebugFont::operator <<(_DFP_ param)
{
	switch (param)
	{
	case myGame::DF_draw:
		// BeginSceneテスト
		bool IsBegin = false;
		if (FAILED(Direct3D9::getInst()->device()->BeginScene()))
			IsBegin = true;	// すでにBeginSceneが呼ばれている

		// 現在蓄えられている文字列を描画
		if (!m_pFont) {
			mStr = _T("");
			return *this;
		}

		RECT R;
		SetRect(&R, 0, 0, 0, 0);
		m_pFont->DrawText(NULL, mStr.c_str(), -1, &R, DT_LEFT | DT_CALCRECT, 0xffffffff);
		OffsetRect(&R, mX * mD3DFD.Width, mY * mD3DFD.Height);
		m_pFont->DrawText(NULL, mStr.c_str(), -1, &R, DT_LEFT, 0xffffffff);

		// 文字バッファをクリア
		mStr = _T("");

		if (!IsBegin) {
			Direct3D9::getInst()->device()->EndScene();
		}
	}
	return *this;
}

//-------------------------------------------------------------------------------------------------
/// 位置設定簡易指定用演算子
DebugFont& DebugFont::operator ()(int x, int y)
{
	mX = x;
	mY = y;
	return *this;
}

} // namespace
// EOF
