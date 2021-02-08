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

/// Direct3D用デバッグフォントクラス
class DebugFont : public Singleton<DebugFont>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	DebugFont();
	~DebugFont();
	//@}

	/// 描画関数
	//@{
	/// 文字列のみ描画
	void draw(const LPCTSTR aString);
	void draw(const LPCTSTR aString, float aX, float aY);
	/// 変数込み描画
	/*template <typename... T>
	void draw(LPCTSTR aString, T... a);*/
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// フォントオブジェクトポインタ
	LPD3DXFONT m_pFont;
	/// フォント属性
	D3DXFONT_DESC mD3DFD;
	//@}

};

} // namespace
// EOF
