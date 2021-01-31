#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Direct3D9::Direct3D9()
	: mD3DInterface(NULL)
	, mD3DDevice(NULL)
	, mParams()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Direct3D9::~Direct3D9()
{
	if (mD3DDevice) {
		SAFE_RELEASE(mD3DDevice);
	}
	if (mD3DInterface) {
		SAFE_RELEASE(mD3DInterface);
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool Direct3D9::initialize(const HWND& a_hWnd)
{
	m_hWnd = a_hWnd;

	ZeroMemory(&mParams, sizeof(D3DPRESENT_PARAMETERS));

	// インターフェースの作成
	if (!createInterface()) {
		MessageBox(NULL, TEXT("インターフェースの作成に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// プレゼンテーションパラメーターの設定
	if (!setupPresentParams()) {
		MessageBox(NULL, TEXT("プレゼンテーションパラメーターの設定に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// デバイスの作成
	if (!createDeveice()) {
		MessageBox(NULL, TEXT("デバイスの作成に失敗しました。"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// ビューポートの設定
	if (!setupViewPort()) {
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
LPDIRECT3DDEVICE9 Direct3D9::device() const
{
	return mD3DDevice;
}

//-------------------------------------------------------------------------------------------------
/// 作成したプレゼンテーションパラメータを返す
const D3DPRESENT_PARAMETERS& Direct3D9::params()
{
	return mParams;
}

//-------------------------------------------------------------------------------------------------
/// インターフェースの作成
bool Direct3D9::createInterface()
{
	if (NULL == (mD3DInterface = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// プレゼンテーションパラメーターの設定
bool Direct3D9::setupPresentParams()
{
	if (Define::WindowModeFlag)
	{
		// フォーマットは今の画面モードに従う
		mParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// ウィンドウモード
		mParams.Windowed = TRUE;
	} else {
		// 現在のプライマリディスプレイアダプタのモードを取得する
		D3DDISPLAYMODE displayMode;

		// ディスプレイモード取得
		if (FAILED(mD3DInterface->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode))) {
			MessageBox(NULL, TEXT("ディスプレイモードの取得に失敗しました"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return false;
		}

		// バックバッファの高さ
		mParams.BackBufferHeight = displayMode.Height;
		// バックバッファの幅
		mParams.BackBufferWidth = displayMode.Width;
		// バックバッファのフォーマット
		mParams.BackBufferFormat = displayMode.Format;
		// フルスクリーンモード
		mParams.Windowed = FALSE;
	}

	// バックバッファの数
	mParams.BackBufferCount = 1;
	// マルチサンプリングは行わない
	mParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	mParams.MultiSampleQuality = 0;
	// Direct3Dにスワップエフェクトを任せる
	mParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// Direct3Dに深度バッファの管理を任せる
	mParams.EnableAutoDepthStencil = TRUE;
	// 深度バッファのフォーマット（通常はこの値で問題ない）
	mParams.AutoDepthStencilFormat = D3DFMT_D16;
	// カバーウィンドウ＝アプリケーションのウィンドウ
	mParams.hDeviceWindow = m_hWnd;
	// フラグは使わない
	mParams.Flags = 0;
	// 今のリフレッシュレートをそのまま使う
	mParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// モニタの垂直回帰を待たない
	mParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// デバイスの作成
bool Direct3D9::createDeveice()
{
	// デバイスの生成( HAL / HARDWARE )
	if (FAILED(mD3DInterface->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&mParams,
		&mD3DDevice
	))) {
		// デバイスの生成( HAL / SOFTWARE )
		if (FAILED(mD3DInterface->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&mParams,
			&mD3DDevice
		))) {
			// デバイスの生成( REF / SOFTWARE )
			if (FAILED(mD3DInterface->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				m_hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&mParams,
				&mD3DDevice
			))) {
				return false;
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ビューポートの設定
bool Direct3D9::setupViewPort()
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = mParams.BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = mParams.BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(mD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// フォントデバイスの作成
bool Direct3D9::createFontDevice()
{

	return true;
}

//-------------------------------------------------------------------------------------------------
/// まだ理解しきれていない部分の設定
bool Direct3D9::setupEtc()
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
