#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "MainLoop.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param hInst �C���X�^���X�n���h��
SystemMain::SystemMain(HINSTANCE hInst)
	: m_hInst(hInst)
	, m_pD3D(NULL)
	, m_pD3DDevice(NULL)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
/// @detail �e��I�u�W�F�N�g��j������
SystemMain::~SystemMain()
{
	if (m_pD3D) {
		// Direct3D�̊J��
		releaseDirect3D();
	}
	if (m_hWnd) {
		// �E�B���h�E�̔j��
		DestroyWindow(m_hWnd);
		UnregisterClass(Define::WindowName, m_hInst);
	}
	if (m_hMutex) {
		// Mutex�̊J��
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// �A�v�����̃E�B���h�E�v���V�[�W���[
/// @detail �{����WndProc����Ăяo����Ă���
LRESULT SystemMain::myWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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
/// ����������
bool SystemMain::initialize()
{
	// ���d�N���̃`�F�b�N
	if (!checkMultiple()) {
		// ���ɋN������Ă���A�v���P�[�V������O�ʂɕ\�����ďI��
		return false;
	}
	// �E�B���h�E������
	if (!initializeWindow()) {
		MessageBox(NULL, TEXT("�E�B���h�E�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// Direct3D������
	if (!initializeDirect3D()) {
		MessageBox(NULL, TEXT("Direct3D�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �S�Ă̏������ɐ���������E�C���h�E��\��
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
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
			// �Q�[���̃��C�����[�v
			if (!mainLoop.loop()) {
				break;
			}
			// fps�𒲐�����
			mFps.adjust();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ���d�N�����`�F�b�N����
bool SystemMain::checkMultiple()
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
/// �E�B���h�E������������
bool SystemMain::initializeWindow()
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
			m_hInst,
			NULL
		);

	// �쐬�����E�B���h�E�̃T�C�Y�ƈʒu��ύX
	RECT wndRect, cltRect;
	GetWindowRect(m_hWnd, &wndRect);
	GetClientRect(m_hWnd, &cltRect);

	// ��N���C�A���g�̈�����Z�����T�C�Y���v�Z
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::WindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::WindowHeight;

	// �ړ�
	SetWindowPos(
		m_hWnd,
		NULL,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // ���j�^�[�̒����ɕ\��
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // ''
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);

	// �E�B���h�E�̍쐬�ɐ������Ă��邩���`�F�b�N
	if (!m_hWnd) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// Direct3D������������
bool SystemMain::initializeDirect3D()
{
	// D3D�I�u�W�F�N�g�̐���
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	// �v���[���e�[�V�����p�����[�^
	//D3DPRESENT_PARAMETERS m_D3DPParams;
	ZeroMemory(&mD3DPParams, sizeof(D3DPRESENT_PARAMETERS));

	if (Define::FullScreenMode)
	{
		// ���݂̃v���C�}���f�B�X�v���C�A�_�v�^�̃��[�h���擾����
		D3DDISPLAYMODE displayMode;

		if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		{
			MessageBox(NULL, TEXT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return false;
		}

		// �o�b�N�o�b�t�@�̍���
		mD3DPParams.BackBufferHeight = displayMode.Height;
		// �o�b�N�o�b�t�@�̕�
		mD3DPParams.BackBufferWidth = displayMode.Width;
		// �o�b�N�o�b�t�@�̃t�H�[�}�b�g
		mD3DPParams.BackBufferFormat = displayMode.Format;
		// �t���X�N���[�����[�h
		mD3DPParams.Windowed = FALSE;
	} else {
		// �t�H�[�}�b�g�͍��̉�ʃ��[�h�ɏ]��
		mD3DPParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// �E�B���h�E���[�h
		mD3DPParams.Windowed = TRUE;
	}

	// �o�b�N�o�b�t�@�̐�
	mD3DPParams.BackBufferCount = 1;
	// �}���`�T���v�����O�͍s��Ȃ�
	mD3DPParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	mD3DPParams.MultiSampleQuality = 0;
	// Direct3D�ɃX���b�v�G�t�F�N�g��C����
	mD3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	mD3DPParams.EnableAutoDepthStencil = TRUE;
	// �[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
	mD3DPParams.AutoDepthStencilFormat = D3DFMT_D16;
	// �J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
	mD3DPParams.hDeviceWindow = m_hWnd;
	// �t���O�͎g��Ȃ�
	mD3DPParams.Flags = 0;
	// ���̃��t���b�V�����[�g�����̂܂܎g��
	mD3DPParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// ���j�^�̐�����A��҂��Ȃ�
	mD3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// �f�o�C�X�̐���( HAL / HARDWARE )
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
	{
		// �f�o�C�X�̐���( HAL / SOFTWARE )
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
		{
			// �f�o�C�X�̐���( REF / SOFTWARE )
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &mD3DPParams, &m_pD3DDevice)))
			{
				return false;
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

	return true;
}

//-------------------------------------------------------------------------------------------------
/// Direct3D���J������
void SystemMain::releaseDirect3D()
{
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}

} // namespace
// EOF
