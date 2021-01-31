#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
#include <tchar.h>
#include "Direct3D9.h"
#include "Macros.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Mesh::Mesh()
{
	// �[���N���A
	for (int i = 0; i < (int)MeshList::TERM; i++) {
		ZeroMemory(&mXFile[i], sizeof(XFile));
	}

	// �e���b�V���̃t�@�C���p�X���w��
	mFilePath[(int)MeshList::TestMan] = TEXT("res/mesh/f-mine.x");

}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Mesh::~Mesh()
{
	// �j�����Y����`�F�b�N
	for (int i = 0; i < (int)MeshList::TERM; i++) {
		if (mXFile[i].mesh) {
			release(i);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ����������
void Mesh::initialize()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aMeshList �`�悷�郁�b�V��
/// @param aTransform �`�悷��ʒu�A��]�A�X�P�[��
void Mesh::draw(MeshList aMeshList, Transform aTransform)
{
	XFile* xFile = &mXFile[(int)aMeshList];
	if (xFile == nullptr) {
		MessageBox(NULL, TEXT("�`�悷�郁�b�V�����ǂݍ��߂Ă��܂���"), TEXT("MESH_ERROR"), MB_OK | MB_ICONSTOP);
		return;
	}

	// �ʒu�p�s��
	D3DXMATRIX posMatrix;
	// ��]�p�s��
	D3DXMATRIX rotMatrix;
	// ���ʂ̍s��
	D3DXMATRIX resultMatrix;

	// �P�ʍs������߂�
	D3DXMatrixIdentity(&posMatrix);
	D3DXMatrixIdentity(&rotMatrix);
	D3DXMatrixIdentity(&resultMatrix);

	// ���s�ړ��Ɖ�]�̍s���ݒ�
	D3DXMatrixTranslation(&posMatrix, aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	D3DXMatrixRotationYawPitchRoll(&rotMatrix, aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);

	// �s��̍���
	resultMatrix = rotMatrix * posMatrix;

	// �`��f�B�o�C�X�֓K�p
	Direct3D9::getInst()->device()->SetTransform(D3DTS_WORLD, &resultMatrix);

	// �}�e���A���̐��������[�v
	for (DWORD i = 0; i < xFile->materialNum; i++)
	{
		// �T�u�Z�b�g�Ƀ}�e���A���ƃe�N�X�`����ݒ�B
		Direct3D9::getInst()->device()->SetMaterial(&(xFile->materials[i]));
		Direct3D9::getInst()->device()->SetTexture(0, xFile->textures[i]);

		// ���b�V���E�T�u�Z�b�g�̕`��B
		xFile->mesh->DrawSubset(i);
	}
}

//-------------------------------------------------------------------------------------------------
/// �ǂݍ���
/// @param aMeshList �ǂݍ��ރ��b�V��
/// @return �ǂݍ��݂ɐ�����������Ԃ�
bool Mesh::load(MeshList aMeshList)
{
	// �ǂݍ��ރt�@�C���p�X��X�t�@�C��
	LPCTSTR meshFilePath = mFilePath[(int)aMeshList];
	XFile* xFile = &mXFile[(int)aMeshList];

	// X�t�@�C���̓ǂݍ���
	LPD3DXBUFFER pD3DXMtrlBuffer;
	if (FAILED(D3DXLoadMeshFromX(
		meshFilePath,
		D3DXMESH_SYSTEMMEM,
		Direct3D9::getInst()->device(),
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&(xFile->materialNum),
		&(xFile->mesh)
	))) {
		// �G���[
		TCHAR errorMsg[512];
		_stprintf_s(errorMsg, 256, TEXT("X�t�@�C���w%s�x��������܂���ł����B"), meshFilePath);
		MessageBox(NULL, errorMsg, TEXT("MESH_ERROR"), MB_OK);

		return false;
	}

	// pD3DXMtrlBuffer����A�}�e���A����e�N�X�`���̖��̂Ȃǂ̏����擾����B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	xFile->materials = new D3DMATERIAL9[xFile->materialNum];
	xFile->textures = new LPDIRECT3DTEXTURE9[xFile->materialNum];

	// material
	for (DWORD i = 0; i < xFile->materialNum; i++) {
		// material�̃R�s�[
		xFile->materials[i] = d3dxMaterials[i].MatD3D;
		// material�Ɋ�����ݒ肷��
		xFile->materials[i].Ambient = xFile->materials[i].Diffuse;

		// texture�̃t�@�C���p�X
		/*TCHAR* textureName = NULL;
		MultiByteToWideChar(CP_ACP, 0, d3dxMaterials->pTextureFilename, -1, textureName, 256);
		TCHAR textureFilePath[256];
		_stprintf_s(textureFilePath, sizeof(textureFilePath), TEXT("res/mesh/%s"), textureName);*/

		// �e�N�X�`���̓ǂݍ���
		xFile->textures[i] = NULL;
		if (d3dxMaterials->pTextureFilename != NULL && lstrlenA(d3dxMaterials->pTextureFilename) > 0) {
			if (FAILED(D3DXCreateTextureFromFileA(
				Direct3D9::getInst()->device(),
				d3dxMaterials->pTextureFilename,
				&(xFile->textures[i])
			))) {
				// �G���[
				TCHAR errorMsg[256];
				_stprintf_s(
					errorMsg,
					256,
					TEXT("X�t�@�C���w%s�x�Ŏw�肳�ꂽ�e�N�X�`���}�b�v�t�@�C���w%s�x��������܂���ł����B"),
					meshFilePath,
					d3dxMaterials->pTextureFilename
				);
				MessageBox(NULL, errorMsg, TEXT("MESH_ERROR"), MB_OK);

				return false;
			}
		}
	}

	SAFE_RELEASE(pD3DXMtrlBuffer);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �j��
/// @param aMeshList �j�����郁�b�V��
void Mesh::release(MeshList aMeshList)
{
	// �ǂݍ���X�t�@�C��
	XFile* xFile = &mXFile[(int)aMeshList];

	// �G���[�`�F�b�N
	if (!xFile->mesh) {
		MessageBox(NULL, TEXT("�j�����������b�V����������܂���ł����B"), TEXT("MESH_ERROR"), MB_OK);
		return;
	}

	//���b�V���}�e���A���̉��
	SAFE_DELETE_ARRAY(xFile->materials);

	//�e�N�X�`���̉��
	if (xFile->textures) {
		for (DWORD i = 0; i < xFile->materialNum; i++) {
			SAFE_RELEASE(xFile->textures[i]);
		}
		SAFE_DELETE_ARRAY(xFile->textures);
	}

	//���b�V���̊J��
	SAFE_RELEASE(xFile->mesh);
}


//-------------------------------------------------------------------------------------------------
/// �j���i�f�X�g���N�^�p�j
/// @param aMeshList �j�����郁�b�V��
void Mesh::release(int aNum)
{
	// �ǂݍ���X�t�@�C��
	XFile* xFile = &mXFile[aNum];

	// �G���[�`�F�b�N
	if (!xFile->mesh) {
		MessageBox(NULL, TEXT("�j�����������b�V����������܂���ł����B"), TEXT("MESH_ERROR"), MB_OK);
		return;
	}

	//���b�V���}�e���A���̉��
	SAFE_DELETE_ARRAY(xFile->materials);

	//�e�N�X�`���̉��
	if (xFile->textures) {
		for (DWORD i = 0; i < xFile->materialNum; i++) {
			SAFE_RELEASE(xFile->textures[i]);
		}
		SAFE_DELETE_ARRAY(xFile->textures);
	}

	//���b�V���̊J��
	SAFE_RELEASE(xFile->mesh);
}

} // namespace
// EOF