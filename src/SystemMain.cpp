#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param hInst インスタンスハンドル
SystemMain::SystemMain(HINSTANCE hInst)
	: m_hInst(hInst)
	, m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
/// @detail 各種オブジェクトを破棄する
SystemMain::~SystemMain()
{
	if (m_pD3D) {
		// Direct3Dの開放
		releaseDirect3D();
	}
	if (m_hWnd) {
		// ウィンドウの破棄
		DestroyWindow(m_hWnd);
		UnregisterClass(Define::WindowName, m_hInst);
	}
	if (m_hMutex) {
		// Mutexの開放
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// アプリ内のウィンドウプロシージャー
/// @detail 本物のWndProcから呼び出されている
LRESULT SystemMain::myWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_KEYDOWN:
		// キーを押した時
		switch ((char)wParam) {
		case VK_ESCAPE:
			// ESC
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		// 閉じるボタンをクリックした時
		PostQuitMessage(0);
		break;
	}
	// 上記以外のメッセージはWindowsへ処理を任せる
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool SystemMain::initialize()
{
	// 多重起動のチェック
	if (!checkMultiple()) {
		// 既に起動されているアプリケーションを前面に表示して終了
		return false;
	}
	// ウィンドウ初期化
	if (!initializeWindow()) {
		MessageBox(NULL, TEXT("ウィンドウの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// Direct3D初期化
	if (!initializeDirect3D()) {
		MessageBox(NULL, TEXT("Direct3Dの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// 全ての初期化に成功したらウインドウを表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	MainLoop mainLoop(m_pD3DDevice);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OSからのメッセージをウィンドウプロシージャーに渡す
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// ゲームのメインループ
			if (!mainLoop.loop()) {
				break;
			}
			// fpsを調整する
			mFps.adjust();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 多重起動をチェックする
bool SystemMain::checkMultiple()
{
	m_hMutex = CreateMutex(NULL, FALSE, Define::WindowName);
	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS)
	{
		// 既に起動しているウィンドウを前面表示する
		HWND hWnd = FindWindow(Define::WindowName, NULL);
		if (IsIconic(hWnd))
		{
			// メイン・ウィンドウが最小化されていれば元に戻す
			ShowWindowAsync(hWnd, SW_RESTORE);
		}
		SetForegroundWindow(hWnd);

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウを初期化する
bool SystemMain::initializeWindow()
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = Define::WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// ウィンドウクラスを登録
	RegisterClassEx(&wc);

	// ウィンドウの作成
	m_hWnd =
		CreateWindow(
			Define::WindowName,
			Define::WindowName,
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), // 最大化ボタンとサイズ変更を無効
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			m_hInst,
			NULL
		);

	// 作成したウィンドウのサイズと位置を変更
	RECT wndRect, cltRect;
	GetWindowRect(m_hWnd, &wndRect);
	GetClientRect(m_hWnd, &cltRect);

	// 非クライアント領域を加算したサイズを計算
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::WindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::WindowHeight;

	// 移動
	SetWindowPos(
		m_hWnd,
		NULL,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // モニターの中央に表示
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // ''
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);

	// ウィンドウの作成に成功しているかをチェック
	if (!m_hWnd) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// Direct3Dを初期化する
bool SystemMain::initializeDirect3D()
{
	// D3Dオブジェクトの生成
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	// プレゼンテーションパラメータ
	//D3DPRESENT_PARAMETERS m_D3DPParams;
	ZeroMemory(&mD3DPParams, sizeof(D3DPRESENT_PARAMETERS));

	if (Define::FullScreenMode)
	{
		// 現在のプライマリディスプレイアダプタのモードを取得する
		D3DDISPLAYMODE displayMode;

		if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		{
			MessageBox(NULL, TEXT("ディスプレイモードの取得に失敗しました"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return false;
		}

		// バックバッファの高さ
		mD3DPParams.BackBufferHeight = displayMode.Height;
		// バックバッファの幅
		mD3DPParams.BackBufferWidth = displayMode.Width;
		// バックバッファのフォーマット
		mD3DPParams.BackBufferFormat = displayMode.Format;
		// フルスクリーンモード
		mD3DPParams.Windowed = FALSE;
	} else {
		// フォーマットは今の画面モードに従う
		mD3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// ウィンドウモード
		mD3DPParams.Windowed = TRUE;
	}

	// バックバッファの数
	mD3DPParams.BackBufferCount = 1;
	// マルチサンプリングは行わない
	mD3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	mD3DPParams.MultiSampleQuality = 0;
	// Direct3Dにスワップエフェクトを任せる
	mD3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// Direct3Dに深度バッファの管理を任せる
	mD3DPParams.EnableAutoDepthStencil = TRUE;
	// 深度バッファのフォーマット（通常はこの値で問題ない）
	mD3DPParams.AutoDepthStencilFormat = D3DFMT_D16;
	// カバーウィンドウ＝アプリケーションのウィンドウ
	mD3DPParams.hDeviceWindow = m_hWnd;
	// フラグは使わない
	mD3DPParams.Flags = 0;
	// 今のリフレッシュレートをそのまま使う
	mD3DPParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// モニタの垂直回帰を待たない
	mD3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// デバイスの生成( HAL / HARDWARE )
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
	{
		// デバイスの生成( HAL / SOFTWARE )
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
		{
			// デバイスの生成( REF / SOFTWARE )
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
			{
				return false;
			}
		}
	}

	// 後で変更しないレンダリングステートの設定
	// Zバッファを有効にする
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// ポリゴンの裏は表示しない
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ライトを有効に
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// 環境光
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);

	// 光源（ライト）の設定
	// ライトを有効に
	m_pD3DDevice->LightEnable(0, TRUE);

	// テクスチャステージステートの設定
	// テクスチャの色を使用
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// 乗算する
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// フィルタの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// Direct3Dを開放する
void SystemMain::releaseDirect3D()
{
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}

} // namespace
// EOF
