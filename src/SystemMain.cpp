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
		UnregisterClass(Define::WindowName, m_hInst);
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

	// �E�C���h�E��\��
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
	wc.lpszClassName = Define::WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// �E�B���h�E�N���X��o�^
	RegisterClassEx(&wc);

	// �E�B���h�E�̍쐬
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
			wc.hInstance,
			NULL
		);

	// �쐬�����E�B���h�E�̃T�C�Y�ƈʒu��ύX
	RECT rw, rc;
	GetWindowRect(m_hWnd, &rw);
	GetClientRect(m_hWnd, &rc);
	int sx = ((rw.right - rw.left) - (rc.right - rc.left)) + Define::WindowWidth;  // ��N���C�A���g�̈�����Z�����T�C�Y
	int sy = ((rw.bottom - rw.top) - (rc.bottom - rc.top)) + Define::WindowHeight; // ''

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
	if (Define::FullScreenMode)
	{
		// ���݂̃v���C�}���f�B�X�v���C�A�_�v�^�̃��[�h���擾����
		D3DDISPLAYMODE displayMode;

		if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		{
			MessageBox(NULL, TEXT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return(E_FAIL);
		}

		// �o�b�N�o�b�t�@�̍���
		m_D3DPParams.BackBufferHeight = displayMode.Height;
		// �o�b�N�o�b�t�@�̕�
		m_D3DPParams.BackBufferWidth = displayMode.Width;
		// �o�b�N�o�b�t�@�̃t�H�[�}�b�g
		m_D3DPParams.BackBufferFormat = displayMode.Format;
		// �t���X�N���[�����[�h
		m_D3DPParams.Windowed = FALSE;
	} else {
		// �t�H�[�}�b�g�͍��̉�ʃ��[�h�ɏ]��
		m_D3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// �E�B���h�E���[�h
		m_D3DPParams.Windowed = TRUE;
	}

	// ���ʃp�����[�^
	// �o�b�N�o�b�t�@�̐�
	m_D3DPParams.BackBufferCount = 1;

	// �}���`�T���v�����O�͍s��Ȃ�
	m_D3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPParams.MultiSampleQuality = 0;

	// Direct3D�ɃX���b�v�G�t�F�N�g��C����
	m_D3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	m_D3DPParams.EnableAutoDepthStencil = TRUE;
	// �[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
	m_D3DPParams.AutoDepthStencilFormat = D3DFMT_D16;

	// �J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
	m_D3DPParams.hDeviceWindow = m_hWnd;

	// �t���O�͎g��Ȃ�
	m_D3DPParams.Flags = 0;

	// ���̃��t���b�V�����[�g�����̂܂܎g��
	m_D3DPParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// ���j�^�̐�����A��҂�
	m_D3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

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
	// Z�o�b�t�@��L���ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// �|���S���̗��͕\�����Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���C�g��L����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);

	// �����i���C�g�j�̐ݒ�
	// ���C�g��L����
	m_pD3DDevice->LightEnable(0, TRUE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	// �e�N�X�`���̐F���g�p
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// ��Z����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// �t�B���^�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

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
