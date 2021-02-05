#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <d3dx9.h>
#include "Singleton.h"
#include "MeshList.h"
#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ���b�V���iX�t�@�C�����g�p�j
class Mesh : public Singleton<Mesh>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Mesh();
	~Mesh();
	//@}

	/// @name ����������
	//@{
	void initialize();
	//@}

	/// @name �`��/�ǂݍ���/�j��
	//@{
	bool draw(MeshList aMeshList, Transform aTransform);
	bool load(MeshList aMeshList);
	void release(MeshList aMeshList);
	//@}

private:
	/// @name X�t�@�C���\����
	//@{ 
	struct XFileData
	{
		/// ���b�V���}�e���A��
		D3DMATERIAL9* materials;
		/// �e�N�X�`���f�[�^
		LPDIRECT3DTEXTURE9* textures;
		/// ���b�V��
		LPD3DXMESH mesh;
		/// ���b�V����
		DWORD materialNum;
	};
	//@}

	// @name �ǂݍ��񂾃��b�V����j������i�f�X�g���N�^�p�j
	//@{
	void release(int aNum);
	//@}

	// @name �v���C�x�[�g�����o�ϐ�
	//@{
	XFileData mXFile[(int)MeshList::TERM];
	LPCTSTR mFilePath[(int)MeshList::TERM];
	//@}

};

} // namespace
// EOF
