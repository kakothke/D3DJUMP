#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
SystemMain::SystemMain(HINSTANCE hInst)
	: m_hInst(hInst)
	, m_hWnd()
	, m_pD3D(NULL)
	, m_D3DPParams()
	, m_pD3DDevice(NULL)
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// デストラクタ
/// </summary>
SystemMain::~SystemMain()
{
	ReleaseDirect3D();
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// ウィンドウプロシージャー
/// </summary>
LRESULT SystemMain::MyWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_KEYDOWN: // キーを押した時
		switch ((char)wParam) {
		case VK_ESCAPE: // ESC
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY: // 閉じるボタンをクリックした時
		PostQuitMessage(0);
		break;
	}
	// 上記以外のメッセージはWindowsへ処理を任せる
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// 初期化処理
/// </summary>
bool SystemMain::Init()
{
	// ウィンドウ初期化
	if (FAILED(InitWindow())) {
		MessageBox(NULL, TEXT("ウィンドウの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	// Direct3D初期化
	if (FAILED(InitDirect3D())) {
		MessageBox(NULL, TEXT("Direct3Dの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// メッセージループとアプリケーション処理の入り口
/// </summary>
void SystemMain::MsgLoop()
{
	// メッセージループ
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// アプリケーションの処理はここから飛ぶ。
			Render();
		}
	}
	// アプリケーションの終了
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// ウィンドウ初期化
/// </summary>
HRESULT SystemMain::InitWindow()
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
	wc.lpszClassName = Define::Window_Name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// ウィンドウクラスを登録
	RegisterClassEx(&wc);

	// ウィンドウの作成
	m_hWnd =
		CreateWindow(
			Define::Window_Name,
			Define::Window_Name,
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), // 最大化ボタンとサイズ変更を無効
			(GetSystemMetrics(SM_CXSCREEN) - Define::Window_Width) / 2,  // ディスプレイの中央に表示（x）
			(GetSystemMetrics(SM_CYSCREEN) - Define::Window_Height) / 2, // ディスプレイの中央に表示（y）
			Define::Window_Width,
			Define::Window_Height,
			NULL,
			NULL,
			m_hInst,
			NULL
		);
	if (!m_hWnd) {
		return E_FAIL;
	}

	// ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// Direct3D初期化
/// </summary>
HRESULT SystemMain::InitDirect3D()
{
	// D3Dオブジェクトの生成
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		return (E_FAIL);
	}

	// PRESENTパラメータをゼロクリア
	ZeroMemory(&m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS));

	// プレゼンテーションパラメータ
	m_D3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;
	m_D3DPParams.Windowed = TRUE;
	m_D3DPParams.BackBufferCount = 1; // バックバッファの数
	m_D3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPParams.EnableAutoDepthStencil = TRUE;	// Direct3Dに深度バッファの管理を任せる
	m_D3DPParams.AutoDepthStencilFormat = D3DFMT_D16; // 深度バッファのフォーマット

	m_D3DPParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 今のリフレッシュレートをそのまま使う

	// D3Dデバイスの生成
	// HAL / HARDWARE
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPParams, &m_pD3DDevice)))
	{
		// HAL / SOFTWARE
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPParams, &m_pD3DDevice)))
		{
			// REF / SOFTWARE
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPParams, &m_pD3DDevice)))
			{
				return(E_FAIL);
			}
		}
	}

	// 後で変更しないレンダリングステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Zバッファを有効にする。
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// ポリゴンの裏は表示しない。
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ライトを有効に

	// シェーディングモードの変更。
	// g_pD3DDevice->SetRenderState( D3DRS_SHADEMODE , D3DSHADE_FLAT );

	// フィルタの設定、D3DTEXF_POINTをD3DTEXF_LINEARに変更してテクスチャの変化の仕方を見るとかすると楽しい
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	m_pD3DDevice->Reset(&m_D3DPParams);

	return (S_OK);
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// Direct3Dの開放
/// </summary>
void SystemMain::ReleaseDirect3D()
{
	m_pD3DDevice->Release();
	m_pD3DDevice = NULL;

	m_pD3D->Release();
	m_pD3D = NULL;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// 描画処理
/// </summary>
void SystemMain::Render()
{
	// Zバッファとバックバッファをクリア
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 64), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene())) {
		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファを表画面に描画
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

} // namespace
