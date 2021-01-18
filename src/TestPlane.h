#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

//-------------------------------------------------------------------------------------------------
namespace MyGame {

//-------------------------------------------------------------------------------------------------
/// テストオブジェクト
class TestPlane
{
public:
	TestPlane();
	~TestPlane();
	void Render() const;

private:
	/// モデルの位置、回転、スケールを扱う構造体
	struct Transform
	{
		/// 位置
		D3DXVECTOR3	pos;
		/// 回転
		D3DXVECTOR3	rot;
		/// スケール
		D3DXVECTOR3	scale;
		/// オブジェクトのモデルの種類
		int modelType;
		/// 親オブジェクトの番号
		int	parent;
		/// オブジェクトを表示するか
		bool isActive;
	};

	struct TheModels
	{
		/// システム中のメッシュオブジェクト
		LPD3DXMESH mesh;
		/// メッシュの質感(materials)
		D3DMATERIAL9* meshMaterials;
		/// メッシュのテクスチャ(texture)
		LPDIRECT3DTEXTURE9* meshTextures;
		/// メッシュ質感の数
		DWORD materialNum;
	};

	Transform mTransform;
	TheModels mTheModels;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	LPCTSTR mFileName;
	

	bool LoadModelsFromXFile();

};

} // namespace
