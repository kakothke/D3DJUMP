#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// �e�X�g�I�u�W�F�N�g
class TestPlane
{
public:
	TestPlane();
	~TestPlane();
	void Render() const;

private:
	/// ���f���̈ʒu�A��]�A�X�P�[���������\����
	struct Transform
	{
		/// �ʒu
		D3DXVECTOR3	pos;
		/// ��]
		D3DXVECTOR3	rot;
		/// �X�P�[��
		D3DXVECTOR3	scale;
		/// �I�u�W�F�N�g�̃��f���̎��
		int modelType;
		/// �e�I�u�W�F�N�g�̔ԍ�
		int	parent;
		/// �I�u�W�F�N�g��\�����邩
		bool isActive;
	};

	struct TheModels
	{
		/// �V�X�e�����̃��b�V���I�u�W�F�N�g
		LPD3DXMESH mesh;
		/// ���b�V���̎���(materials)
		D3DMATERIAL9* meshMaterials;
		/// ���b�V���̃e�N�X�`��(texture)
		LPDIRECT3DTEXTURE9* meshTextures;
		/// ���b�V�������̐�
		DWORD materialNum;
	};

	Transform mTransform;
	TheModels mTheModels;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPCTSTR mFileName;
	

	bool LoadModelsFromXFile();

};

} // namespace
