#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "Macros.h"
#include "Define.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// DirectX9の管理
class DirectX9
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	DirectX9();
	~DirectX9();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize(HWND);
	//@}

	/// @name アクセサ
	//@{
	/// 作成したデバイスを返す
	LPDIRECT3DDEVICE9 device() const;
	//@}

private:
	/// @name 内部実装
	//@{
	/// インターフェースの作成
	bool createInterface();
	/// プレゼンテーションパラメーターの設定
	bool setupPresentParams(D3DPRESENT_PARAMETERS&, HWND);
	/// デバイスの作成
	bool createDeveice(D3DPRESENT_PARAMETERS&, HWND);
	/// ビューポートの設定
	bool setupViewPort(D3DPRESENT_PARAMETERS&);
	/// フォントデバイスの作成
	bool createFontDevice();
	/// まだ理解しきれていない部分の設定
	bool setupEtc();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// インターフェース
	LPDIRECT3D9 mD3DInterface;
	/// レンダリングデバイス
	LPDIRECT3DDEVICE9 mD3DDevice;
	//@}

};

} // namespace
// EOF
