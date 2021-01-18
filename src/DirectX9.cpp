#include "DirectX9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DirectX9::DirectX9()
	: mD3DInterface(NULL)
	, mD3DDevice(NULL)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
DirectX9::~DirectX9()
{
	SAFE_RELEASE(mD3DDevice);
	SAFE_RELEASE(mD3DInterface);
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool DirectX9::initialize(HWND a_hWnd)
{
	D3DPRESENT_PARAMETERS presentParams;
	ZeroMemory(&presentParams, sizeof(D3DPRESENT_PARAMETERS));

	// インターフェースの作成
	if (!createInterface()) {
		MessageBox(NULL, TEXT("インターフェースの作成に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// プレゼンテーションパラメーターの設定
	if (!setupPresentParams(presentParams, a_hWnd)) {
		MessageBox(NULL, TEXT("プレゼンテーションパラメーターの設定に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// デバイスの作成
	if (!createDeveice(presentParams, a_hWnd)) {
		MessageBox(NULL, TEXT("デバイスの作成に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// ビューポートの設定
	if (!setupViewPort(presentParams)) {
		MessageBox(NULL, TEXT("ビューポートの設定に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// フォントデバイスの作成
	if (!createFontDevice()) {
		MessageBox(NULL, TEXT("フォントデバイスの作成に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// その他の設定
	if (!setupEtc()) {
		MessageBox(NULL, TEXT("その他の設定に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 作成したデバイスを返す
LPDIRECT3DDEVICE9 DirectX9::device() const
{
	return mD3DDevice;
}

//-------------------------------------------------------------------------------------------------
/// インターフェースの作成
bool DirectX9::createInterface()
{
	if (NULL == (mD3DInterface = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// プレゼンテーションパラメーターの設定
bool DirectX9::setupPresentParams(D3DPRESENT_PARAMETERS& aPresentParams, HWND a_hWnd)
{
	if (Define::WindowModeFlag)
	{
		// フォーマットは今の画面モードに従う
		aPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// ウィンドウモード
		aPresentParams.Windowed = TRUE;
	} else {
		// 現在のプライマリディスプレイアダプタのモードを取得する
		D3DDISPLAYMODE displayMode;

		// ディスプレイモード取得
		if (FAILED(mD3DInterface->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		{
			MessageBox(NULL, TEXT("ディスプレイモードの取得に失敗しました"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return false;
		}

		// バックバッファの高さ
		aPresentParams.BackBufferHeight = displayMode.Height;
		// バックバッファの幅
		aPresentParams.BackBufferWidth = displayMode.Width;
		// バックバッファのフォーマット
		aPresentParams.BackBufferFormat = displayMode.Format;
		// フルスクリーンモード
		aPresentParams.Windowed = FALSE;
	}

	// バックバッファの数
	aPresentParams.BackBufferCount = 1;
	// マルチサンプリングは行わない
	aPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	aPresentParams.MultiSampleQuality = 0;
	// Direct3Dにスワップエフェクトを任せる
	aPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// Direct3Dに深度バッファの管理を任せる
	aPresentParams.EnableAutoDepthStencil = TRUE;
	// 深度バッファのフォーマット（通常はこの値で問題ない）
	aPresentParams.AutoDepthStencilFormat = D3DFMT_D16;
	// カバーウィンドウ＝アプリケーションのウィンドウ
	aPresentParams.hDeviceWindow = a_hWnd;
	// フラグは使わない
	aPresentParams.Flags = 0;
	// 今のリフレッシュレートをそのまま使う
	aPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// モニタの垂直回帰を待たない
	aPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

//-------------------------------------------------------------------------------------------------
/// デバイスの作成
bool DirectX9::createDeveice(D3DPRESENT_PARAMETERS& aPresentParams, HWND a_hWnd)
{
	// デバイスの生成( HAL / HARDWARE )
	if (FAILED(
		mD3DInterface->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			a_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&aPresentParams,
			&mD3DDevice
		)
	))
	{
		// デバイスの生成( HAL / SOFTWARE )
		if (FAILED(
			mD3DInterface->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				a_hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&aPresentParams,
				&mD3DDevice
			)
		))
		{
			// デバイスの生成( REF / SOFTWARE )
			if (FAILED(
				mD3DInterface->CreateDevice(
					D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					a_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&aPresentParams,
					&mD3DDevice
				)
			))
			{
				return false;
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ビューポートの設定
bool DirectX9::setupViewPort(D3DPRESENT_PARAMETERS& aPresentParams)
{

	return true;
}

//-------------------------------------------------------------------------------------------------
/// フォントデバイスの作成
bool DirectX9::createFontDevice()
{

	return true;
}

//-------------------------------------------------------------------------------------------------
/// まだ理解しきれていない部分の設定
bool DirectX9::setupEtc()
{
	// 後で変更しないレンダリングステートの設定
	// Zバッファを有効にする
	mD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// ポリゴンの裏は表示しない
	mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ライトを有効に
	mD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// 環境光
	mD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);

	// 光源（ライト）の設定
	// ライトを有効に
	mD3DDevice->LightEnable(0, TRUE);

	// テクスチャステージステートの設定
	// テクスチャの色を使用
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// 乗算する
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// フィルタの設定
	mD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	return true;
}

} // namespace
// EOF
