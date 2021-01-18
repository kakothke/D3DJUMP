#include "TestPlane.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
TestPlane::TestPlane()
{
	mTransform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mTransform.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mTransform.modelType = 0;

	mTheModels.mesh = NULL;				// �V�X�e�����̃��b�V���I�u�W�F�N�g
	mTheModels.meshMaterials = NULL;		// ���b�V���̎���(materials)
	mTheModels.meshTextures = NULL;		// ���b�V���̎���(materials)
	mTheModels.materialNum = 0;		// ���b�V�������̐�

	mFileName = TEXT("res/models/f-mine.x");

	if (!LoadModelsFromXFile()) {
		MessageBox(NULL, TEXT("���f���̓ǂݍ��݂Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
TestPlane::~TestPlane()
{
}
//-------------------------------------------------------------------------------------------------
/// <summary>
/// �`��
/// </summary>
void TestPlane::Render() const
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// �f�[�^�̃��[�h
/// </summary>
bool TestPlane::LoadModelsFromXFile()
{
	LPD3DXBUFFER pD3DXMtrlBuf;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(mFileName, D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL, &pD3DXMtrlBuf, NULL, &mTheModels.materialNum, &mTheModels.mesh))) {
		MessageBox(NULL, TEXT("X�t�@�C����������܂���ł����B"), Define::WindowName, MB_OK);
		return false;
	}

	// pD3DXMtrlBuf����A�}�e���A����e�N�X�`���̖��̂Ȃǂ̏����擾����B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuf->GetBufferPointer();
	mTheModels.meshMaterials = new D3DMATERIAL9[mTheModels.materialNum];
	mTheModels.meshTextures = new LPDIRECT3DTEXTURE9[mTheModels.materialNum];

	for (DWORD i0 = 0; i0 < mTheModels.materialNum; i0++) {
		// �����imaterial�j�̃R�s�[
		mTheModels.meshMaterials[i0] = d3dxMaterials[i0].MatD3D;

		// �����imaterial�j�Ɋ�����ݒ肷��iD3DX���������Ȃ����߁j
		mTheModels.meshMaterials[i0].Ambient = mTheModels.meshMaterials[i0].Diffuse;

		mTheModels.meshTextures[i0] = NULL;
		if (d3dxMaterials[i0].pTextureFilename != NULL) {
			if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, (LPCWSTR)d3dxMaterials[i0].pTextureFilename, &(mTheModels.meshTextures[i0])))) {
				MessageBox(NULL, TEXT("X�t�@�C���Ŏw�肳�ꂽ�e�N�X�`���}�b�v�t�@�C����������܂���ł����B"), Define::WindowName, MB_OK);
				return(E_FAIL);
			}
		}
	}

	// �����imaterial�j�o�b�t�@�̊J���B
	pD3DXMtrlBuf->Release();
	pD3DXMtrlBuf = NULL;

	return true;
}

} // namespace
