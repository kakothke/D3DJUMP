#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3d9.h"
#include "d3dx9.h"
#include "Macros.h"
#include "Define.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//-------------------------------------------------------------------------------------------------
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// Direct3D9の管理
class Direct3D9 : public Singleton<Direct3D9>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Direct3D9();
	~Direct3D9();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize(const HWND&);
	//@}

	/// @name アクセサ
	//@{
	/// 作成したデバイスを返す
	LPDIRECT3DDEVICE9 device() const;
	/// 作成したプレゼンテーションパラメータを返す
	const D3DPRESENT_PARAMETERS& params();
	//@}

private:
	/// @name 内部実装
	//@{
	/// インターフェースの作成
	bool createInterface();
	/// プレゼンテーションパラメータの設定
	bool setupPresentParams();
	/// デバイスの作成
	bool createDeveice();
	/// ビューポートの設定
	bool setupViewPort();
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
	/// ウィンドウハンドル
	HWND m_hWnd;
	/// プレゼンテーションパラメータ
	D3DPRESENT_PARAMETERS mParams;
	//@}

};

} // namespace
// EOF
