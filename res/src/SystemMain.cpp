#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
SystemMain::~SystemMain()
{
	if (m_pD3D) {
		// Direct3D�̊J��
		ReleaseDirect3D();
	}

	if (m_hWnd) {
		// �E�B���h�E�̔j��
		UnregisterClass(Define::Window_Name, m_hInst);
	}

	if (m_hMutex) {
		// Mutex�̊J��
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �E�B���h�E�v���V�[�W���[
/// </summary>
LRESULT SystemMain::MyWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
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
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
bool SystemMain::Init()
{
	// ���d�N���̃`�F�b�N
	if (FAILED(CheckMultiple())) {
		// ���ɋN������Ă���A�v���P�[�V������O�ʂɕ\�����ďI��
		return false;
	}

	// �E�B���h�E������
	if (FAILED(InitWindow())) {
		MessageBox(NULL, TEXT("�E�B���h�E�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	// Direct3D������
	if (FAILED(InitDirect3D())) {
		MessageBox(NULL, TEXT("Direct3D�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �E�C���h�E�̕\��
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// ���b�Z�[�W���[�v
/// </summary>
void SystemMain::MsgLoop()
{
	MainLoop mainLoop(m_pD3DDevice);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OS����̃��b�Z�[�W���E�B���h�E�v���V�[�W���[�ɓn��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// �A�v���P�[�V�����̃��C�����[�v
			if (!mainLoop.Loop()) {
				break;
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// ���d�N���̃`�F�b�N
/// </summary>
HRESULT SystemMain::CheckMultiple()
{
	m_hMutex = CreateMutex(NULL, FALSE, Define::Window_Name);
	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS)
	{
		// ���ɋN�����Ă���E�B���h�E��O�ʕ\������
		HWND hWnd = FindWindow(Define::Window_Name, NULL);
		if (IsIconic(hWnd))
		{
			// ���C���E�E�B���h�E���ŏ�������Ă���Ό��ɖ߂�
			ShowWindowAsync(hWnd, SW_RESTORE);
		}
		SetForegroundWindow(hWnd);

		return E_FAIL;
	}

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �E�B���h�E������
/// </summary>
HRESULT SystemMain::InitWindow()
{
	// �E�B���h�E�̒�`
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

	// �E�B���h�E�N���X��o�^
	RegisterClassEx(&wc);

	// �E�B���h�E�̍쐬
	m_hWnd =
		CreateWindow(
			Define::Window_Name,
			Define::Window_Name,
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), // �ő剻�{�^���ƃT�C�Y�ύX�𖳌�
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			wc.hInstance,
			NULL
		);

	// �쐬�����E�B���h�E�̃T�C�Y�ƈʒu��ύX
	RECT rw, rc;
	GetWindowRect(m_hWnd, &rw);
	GetClientRect(m_hWnd, &rc);
	int sx = ((rw.right - rw.left) - (rc.right - rc.left)) + Define::Window_Width;  // ��N���C�A���g�̈�����Z�����T�C�Y
	int sy = ((rw.bottom - rw.top) - (rc.bottom - rc.top)) + Define::Window_Height; // ''

	// �ړ�
	SetWindowPos(
		m_hWnd,
		NULL,
		(GetSystemMetrics(SM_CXSCREEN) - sx) / 2, // ���j�^�[�̒����ɕ\��
		(GetSystemMetrics(SM_CYSCREEN) - sy) / 2, // ''
		sx,
		sy,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);

	// �E�B���h�E�̍쐬�ɐ������Ă��邩���`�F�b�N
	if (!m_hWnd) {
		return E_FAIL;
	}

	return S_OK;
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// Direct3D������
/// </summary>
HRESULT SystemMain::InitDirect3D()
{
	// D3D�I�u�W�F�N�g�̐���
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		return (E_FAIL);
	}

	// PRESENT�p�����[�^���[���N���A
	ZeroMemory(&m_D3DPParams, sizeof(D3DPRESENT_PARAMETERS));

	// �v���[���e�[�V�����p�����[�^
	m_D3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;
	m_D3DPParams.Windowed = TRUE;
	m_D3DPParams.BackBufferCount = 1; // �o�b�N�o�b�t�@�̐�
	m_D3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPParams.EnableAutoDepthStencil = TRUE;	// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	m_D3DPParams.AutoDepthStencilFormat = D3DFMT_D16; // �[�x�o�b�t�@�̃t�H�[�}�b�g

	m_D3DPParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // ���̃��t���b�V�����[�g�����̂܂܎g��

	// D3D�f�o�C�X�̐���
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

	// ��ŕύX���Ȃ������_�����O�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			// Z�o�b�t�@��L���ɂ���B
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// �|���S���̗��͕\�����Ȃ��B
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);			// ���C�g��L����

	// �V�F�[�f�B���O���[�h�̕ύX�B
	// g_pD3DDevice->SetRenderState( D3DRS_SHADEMODE , D3DSHADE_FLAT );

	// �t�B���^�̐ݒ�AD3DTEXF_POINT��D3DTEXF_LINEAR�ɕύX���ăe�N�X�`���̕ω��̎d��������Ƃ�����Ɗy����
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	m_pD3DDevice->Reset(&m_D3DPParams);

	return (S_OK);
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// Direct3D�̊J��
/// </summary>
void SystemMain::ReleaseDirect3D()
{
	m_pD3DDevice->Release();
	m_pD3DDevice = NULL;

	m_pD3D->Release();
	m_pD3D = NULL;
}

} // namespace
