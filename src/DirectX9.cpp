#include "DirectX9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DirectX9::DirectX9()
	: mD3DInterface(NULL)
	, mD3DDevice(NULL)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
DirectX9::~DirectX9()
{
	SAFE_RELEASE(mD3DDevice);
	SAFE_RELEASE(mD3DInterface);
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool DirectX9::initialize(HWND a_hWnd)
{
	D3DPRESENT_PARAMETERS presentParams;
	ZeroMemory(&presentParams, sizeof(D3DPRESENT_PARAMETERS));

	// �C���^�[�t�F�[�X�̍쐬
	if (!createInterface()) {
		MessageBox(NULL, TEXT("�C���^�[�t�F�[�X�̍쐬�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// �v���[���e�[�V�����p�����[�^�[�̐ݒ�
	if (!setupPresentParams(presentParams, a_hWnd)) {
		MessageBox(NULL, TEXT("�v���[���e�[�V�����p�����[�^�[�̐ݒ�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// �f�o�C�X�̍쐬
	if (!createDeveice(presentParams, a_hWnd)) {
		MessageBox(NULL, TEXT("�f�o�C�X�̍쐬�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// �r���[�|�[�g�̐ݒ�
	if (!setupViewPort(presentParams)) {
		MessageBox(NULL, TEXT("�r���[�|�[�g�̐ݒ�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// �t�H���g�f�o�C�X�̍쐬
	if (!createFontDevice()) {
		MessageBox(NULL, TEXT("�t�H���g�f�o�C�X�̍쐬�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}
	// ���̑��̐ݒ�
	if (!setupEtc()) {
		MessageBox(NULL, TEXT("���̑��̐ݒ�Ɏ��s���܂����B"), TEXT("D3D9_ERROR"), MB_OK | MB_ICONSTOP);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �쐬�����f�o�C�X��Ԃ�
LPDIRECT3DDEVICE9 DirectX9::device() const
{
	return mD3DDevice;
}

//-------------------------------------------------------------------------------------------------
/// �C���^�[�t�F�[�X�̍쐬
bool DirectX9::createInterface()
{
	if (NULL == (mD3DInterface = Direct3DCreate9(D3D_SDK_VERSION))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �v���[���e�[�V�����p�����[�^�[�̐ݒ�
bool DirectX9::setupPresentParams(D3DPRESENT_PARAMETERS& aPresentParams, HWND a_hWnd)
{
	if (Define::WindowModeFlag)
	{
		// �t�H�[�}�b�g�͍��̉�ʃ��[�h�ɏ]��
		aPresentParams.BackBufferFormat = D3DFMT_UNKNOWN;
		// �E�B���h�E���[�h
		aPresentParams.Windowed = TRUE;
	} else {
		// ���݂̃v���C�}���f�B�X�v���C�A�_�v�^�̃��[�h���擾����
		D3DDISPLAYMODE displayMode;

		// �f�B�X�v���C���[�h�擾
		if (FAILED(mD3DInterface->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		{
			MessageBox(NULL, TEXT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���"), Define::WindowName, MB_OK | MB_ICONSTOP);
			return false;
		}

		// �o�b�N�o�b�t�@�̍���
		aPresentParams.BackBufferHeight = displayMode.Height;
		// �o�b�N�o�b�t�@�̕�
		aPresentParams.BackBufferWidth = displayMode.Width;
		// �o�b�N�o�b�t�@�̃t�H�[�}�b�g
		aPresentParams.BackBufferFormat = displayMode.Format;
		// �t���X�N���[�����[�h
		aPresentParams.Windowed = FALSE;
	}

	// �o�b�N�o�b�t�@�̐�
	aPresentParams.BackBufferCount = 1;
	// �}���`�T���v�����O�͍s��Ȃ�
	aPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	aPresentParams.MultiSampleQuality = 0;
	// Direct3D�ɃX���b�v�G�t�F�N�g��C����
	aPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// Direct3D�ɐ[�x�o�b�t�@�̊Ǘ���C����
	aPresentParams.EnableAutoDepthStencil = TRUE;
	// �[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
	aPresentParams.AutoDepthStencilFormat = D3DFMT_D16;
	// �J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
	aPresentParams.hDeviceWindow = a_hWnd;
	// �t���O�͎g��Ȃ�
	aPresentParams.Flags = 0;
	// ���̃��t���b�V�����[�g�����̂܂܎g��
	aPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	// ���j�^�̐�����A��҂��Ȃ�
	aPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

//-------------------------------------------------------------------------------------------------
/// �f�o�C�X�̍쐬
bool DirectX9::createDeveice(D3DPRESENT_PARAMETERS& aPresentParams, HWND a_hWnd)
{
	// �f�o�C�X�̐���( HAL / HARDWARE )
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
		// �f�o�C�X�̐���( HAL / SOFTWARE )
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
			// �f�o�C�X�̐���( REF / SOFTWARE )
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
/// �r���[�|�[�g�̐ݒ�
bool DirectX9::setupViewPort(D3DPRESENT_PARAMETERS& aPresentParams)
{

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �t�H���g�f�o�C�X�̍쐬
bool DirectX9::createFontDevice()
{

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �܂�����������Ă��Ȃ������̐ݒ�
bool DirectX9::setupEtc()
{
	// ��ŕύX���Ȃ������_�����O�X�e�[�g�̐ݒ�
	// Z�o�b�t�@��L���ɂ���
	mD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// �|���S���̗��͕\�����Ȃ�
	mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���C�g��L����
	mD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����
	mD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00808080);

	// �����i���C�g�j�̐ݒ�
	// ���C�g��L����
	mD3DDevice->LightEnable(0, TRUE);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	// �e�N�X�`���̐F���g�p
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// ��Z����
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// �t�B���^�̐ݒ�
	mD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	return true;
}

} // namespace
// EOF
