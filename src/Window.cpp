#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
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
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Window::Window()
	: m_hInst()
	, m_hWnd()
	, m_hMutex()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Window::~Window()
{
	// ウィンドウの破棄
	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		UnregisterClass(Define::WindowName, m_hInst);
	}

	// ミューテックスの開放
	if (m_hMutex) {
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool Window::initialize(const HINSTANCE& a_hInst)
{
	m_hInst = a_hInst;

	// 多重起動をチェックする
	if (!checkMultiple()) {
		// 既に起動されているアプリケーションを前面に表示して終了
		return false;
	}
	// ウィンドウクラスを登録する
	if (!registerClass()) {
		MessageBox(NULL, TEXT("ウィンドウクラスの登録に失敗しました。"), TEXT("WINDOW_ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// ウィンドウを作成する
	if (!createWindow()) {
		MessageBox(NULL, TEXT("ウィンドウの作成に失敗しました。"), TEXT("WINDOW_ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 作成したウィンドウハンドルを返す
HWND Window::hWnd() const
{
	return m_hWnd;
}

//-------------------------------------------------------------------------------------------------
/// 多重起動をチェックする
bool Window::checkMultiple()
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
/// ウィンドウクラスを登録する
bool Window::registerClass()
{
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

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウを作成する
bool Window::createWindow()
{
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

	// ウィンドウの作成に成功しているかをチェック
	if (!m_hWnd) {
		return false;
	}
	
	// 非クライアント領域を加算したウィンドウサイズを計算
	RECT wndRect, cltRect;
	GetWindowRect(m_hWnd, &wndRect);
	GetClientRect(m_hWnd, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::WindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::WindowHeight;

	// 作成したウィンドウの位置とサイズを変更
	SetWindowPos(
		m_hWnd,
		NULL,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // モニターの中央に表示
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // モニターの中央に表示
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);

	return true;
}

} // namespace
//EOF
