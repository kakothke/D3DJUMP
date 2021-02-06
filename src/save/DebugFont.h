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

/// DebugFont用フラグ
enum _DFP_
{
	/// 描画指示フラグ
	DF_draw
};

/// Direct3D用デバッグフォントクラス
class DebugFont
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	DebugFont();
	~DebugFont();
	//@}

	/// @name 演算子オーバーロード
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
	/// 位置設定簡易指定用演算子
	DebugFont& operator ()(int x, int y);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// フォントオブジェクトポインタ
	ID3DXFont* m_pFont;
	/// フォント属性
	D3DXFONT_DESC mD3DFD;
	/// 処理用バッファ
	static TCHAR c[24];
	/// 表示位置x
	int mX;
	/// 表示位置y
	int mY;
#if _UNICODE
	/// デバッグ文字列保持バッファ（UNICODE用）
	wstring mStr;
#else
	/// デバッグ文字列保持バッファ（ANCI用）
	string mStr;
#endif
	//@}

};

} // namespace
// EOF
