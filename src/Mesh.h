#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <d3dx9.h>
#include "Transform.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// ���b�V�����X�g
enum class MeshList
{
	TestMan,

	TERM
};

/// X�t�@�C���\����
struct XFile
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
	void draw(MeshList, Transform);
	bool load(MeshList);
	void release(MeshList);
	//@}

private:
	// @name �j���i�f�X�g���N�^�p�j
	//@{
	void release(int aNum);
	//@}

	// @name �v���C�x�[�g�����o�ϐ�
	//@{
	XFile mXFile[(int)MeshList::TERM];
	LPCTSTR mFilePath[(int)MeshList::TERM];
	//@}

	XFile* mTest;

};

} // namespace
// EOF
