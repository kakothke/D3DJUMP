#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		// �L�[����������
		switch ((char)wParam) {
		case VK_ESCAPE:
			// ESC
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		// ����{�^�����N���b�N������
		PostQuitMessage(0);
		break;
	}
	// ��L�ȊO�̃��b�Z�[�W��Windows�֏�����C����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Window::Window()
	: m_hInst()
	, m_hWnd()
	, m_hMutex()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Window::~Window()
{
	// �E�B���h�E�̔j��
	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		UnregisterClass(Define::WindowName, m_hInst);
	}

	// �~���[�e�b�N�X�̊J��
	if (m_hMutex) {
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool Window::initialize(const HINSTANCE& a_hInst)
{
	m_hInst = a_hInst;

	// ���d�N�����`�F�b�N����
	if (!checkMultiple()) {
		// ���ɋN������Ă���A�v���P�[�V������O�ʂɕ\�����ďI��
		return false;
	}
	// �E�B���h�E�N���X��o�^����
	if (!registerClass()) {
		MessageBox(NULL, TEXT("�E�B���h�E�N���X�̓o�^�Ɏ��s���܂����B"), TEXT("WINDOW_ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �E�B���h�E���쐬����
	if (!createWindow()) {
		MessageBox(NULL, TEXT("�E�B���h�E�̍쐬�Ɏ��s���܂����B"), TEXT("WINDOW_ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �쐬�����E�B���h�E�n���h����Ԃ�
HWND Window::hWnd() const
{
	return m_hWnd;
}

//-------------------------------------------------------------------------------------------------
/// ���d�N�����`�F�b�N����
bool Window::checkMultiple()
{
	m_hMutex = CreateMutex(NULL, FALSE, Define::WindowName);
	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS)
	{
		// ���ɋN�����Ă���E�B���h�E��O�ʕ\������
		HWND hWnd = FindWindow(Define::WindowName, NULL);
		if (IsIconic(hWnd))
		{
			// ���C���E�E�B���h�E���ŏ�������Ă���Ό��ɖ߂�
			ShowWindowAsync(hWnd, SW_RESTORE);
		}
		SetForegroundWindow(hWnd);

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E�N���X��o�^����
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

	// �E�B���h�E�N���X��o�^
	RegisterClassEx(&wc);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �E�B���h�E���쐬����
bool Window::createWindow()
{
	m_hWnd =
		CreateWindow(
			Define::WindowName,
			Define::WindowName,
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), // �ő剻�{�^���ƃT�C�Y�ύX�𖳌�
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			m_hInst,
			NULL
		);

	// �E�B���h�E�̍쐬�ɐ������Ă��邩���`�F�b�N
	if (!m_hWnd) {
		return false;
	}
	
	// ��N���C�A���g�̈�����Z�����E�B���h�E�T�C�Y���v�Z
	RECT wndRect, cltRect;
	GetWindowRect(m_hWnd, &wndRect);
	GetClientRect(m_hWnd, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::WindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::WindowHeight;

	// �쐬�����E�B���h�E�̈ʒu�ƃT�C�Y��ύX
	SetWindowPos(
		m_hWnd,
		NULL,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // ���j�^�[�̒����ɕ\��
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // ���j�^�[�̒����ɕ\��
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);

	return true;
}

} // namespace
//EOF
