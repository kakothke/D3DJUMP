#include "Mesh.h"

//-------------------------------------------------------------------------------------------------
#include <tchar.h>
#include "Direct3D9.h"
#include "Macros.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Mesh::Mesh()
{
	// ゼロクリア
	for (int i = 0; i < (int)MeshList::TERM; i++) {
		ZeroMemory(&mXFile[i], sizeof(XFile));
	}

	// 各メッシュのファイルパスを指定
	mFilePath[(int)MeshList::TestMan] = TEXT("res/mesh/f-mine.x");

}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Mesh::~Mesh()
{
	// 破棄し忘れをチェック
	for (int i = 0; i < (int)MeshList::TERM; i++) {
		if (mXFile[i].mesh) {
			release(i);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void Mesh::initialize()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
/// @param aMeshList 描画するメッシュ
/// @param aTransform 描画する位置、回転、スケール
void Mesh::draw(MeshList aMeshList, Transform aTransform)
{
	XFile* xFile = &mXFile[(int)aMeshList];
	if (xFile == nullptr) {
		MessageBox(NULL, TEXT("描画するメッシュが読み込めていません"), TEXT("MESH_ERROR"), MB_OK | MB_ICONSTOP);
		return;
	}

	// 位置用行列
	D3DXMATRIX posMatrix;
	// 回転用行列
	D3DXMATRIX rotMatrix;
	// 結果の行列
	D3DXMATRIX resultMatrix;

	// 単位行列を収める
	D3DXMatrixIdentity(&posMatrix);
	D3DXMatrixIdentity(&rotMatrix);
	D3DXMatrixIdentity(&resultMatrix);

	// 平行移動と回転の行列を設定
	D3DXMatrixTranslation(&posMatrix, aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	D3DXMatrixRotationYawPitchRoll(&rotMatrix, aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);

	// 行列の合成
	resultMatrix = rotMatrix * posMatrix;

	// 描画ディバイスへ適用
	Direct3D9::getInst()->device()->SetTransform(D3DTS_WORLD, &resultMatrix);

	// マテリアルの数だけループ
	for (DWORD i = 0; i < xFile->materialNum; i++)
	{
		// サブセットにマテリアルとテクスチャを設定。
		Direct3D9::getInst()->device()->SetMaterial(&(xFile->materials[i]));
		Direct3D9::getInst()->device()->SetTexture(0, xFile->textures[i]);

		// メッシュ・サブセットの描画。
		xFile->mesh->DrawSubset(i);
	}
}

//-------------------------------------------------------------------------------------------------
/// 読み込み
/// @param aMeshList 読み込むメッシュ
/// @return 読み込みに成功したかを返す
bool Mesh::load(MeshList aMeshList)
{
	// 読み込むファイルパスとXファイル
	LPCTSTR meshFilePath = mFilePath[(int)aMeshList];
	XFile* xFile = &mXFile[(int)aMeshList];

	// Xファイルの読み込み
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
		// エラー
		TCHAR errorMsg[512];
		_stprintf_s(errorMsg, 256, TEXT("Xファイル『%s』が見つかりませんでした。"), meshFilePath);
		MessageBox(NULL, errorMsg, TEXT("MESH_ERROR"), MB_OK);

		return false;
	}

	// pD3DXMtrlBufferから、マテリアルやテクスチャの名称などの情報を取得する。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	xFile->materials = new D3DMATERIAL9[xFile->materialNum];
	xFile->textures = new LPDIRECT3DTEXTURE9[xFile->materialNum];

	// material
	for (DWORD i = 0; i < xFile->materialNum; i++) {
		// materialのコピー
		xFile->materials[i] = d3dxMaterials[i].MatD3D;
		// materialに環境光を設定する
		xFile->materials[i].Ambient = xFile->materials[i].Diffuse;

		// textureのファイルパス
		/*TCHAR* textureName = NULL;
		MultiByteToWideChar(CP_ACP, 0, d3dxMaterials->pTextureFilename, -1, textureName, 256);
		TCHAR textureFilePath[256];
		_stprintf_s(textureFilePath, sizeof(textureFilePath), TEXT("res/mesh/%s"), textureName);*/

		// テクスチャの読み込み
		xFile->textures[i] = NULL;
		if (d3dxMaterials->pTextureFilename != NULL && lstrlenA(d3dxMaterials->pTextureFilename) > 0) {
			if (FAILED(D3DXCreateTextureFromFileA(
				Direct3D9::getInst()->device(),
				d3dxMaterials->pTextureFilename,
				&(xFile->textures[i])
			))) {
				// エラー
				TCHAR errorMsg[256];
				_stprintf_s(
					errorMsg,
					256,
					TEXT("Xファイル『%s』で指定されたテクスチャマップファイル『%s』が見つかりませんでした。"),
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
/// 破棄
/// @param aMeshList 破棄するメッシュ
void Mesh::release(MeshList aMeshList)
{
	// 読み込むXファイル
	XFile* xFile = &mXFile[(int)aMeshList];

	// エラーチェック
	if (!xFile->mesh) {
		MessageBox(NULL, TEXT("破棄したいメッシュが見つかりませんでした。"), TEXT("MESH_ERROR"), MB_OK);
		return;
	}

	//メッシュマテリアルの解放
	SAFE_DELETE_ARRAY(xFile->materials);

	//テクスチャの解放
	if (xFile->textures) {
		for (DWORD i = 0; i < xFile->materialNum; i++) {
			SAFE_RELEASE(xFile->textures[i]);
		}
		SAFE_DELETE_ARRAY(xFile->textures);
	}

	//メッシュの開放
	SAFE_RELEASE(xFile->mesh);
}


//-------------------------------------------------------------------------------------------------
/// 破棄（デストラクタ用）
/// @param aMeshList 破棄するメッシュ
void Mesh::release(int aNum)
{
	// 読み込むXファイル
	XFile* xFile = &mXFile[aNum];

	// エラーチェック
	if (!xFile->mesh) {
		MessageBox(NULL, TEXT("破棄したいメッシュが見つかりませんでした。"), TEXT("MESH_ERROR"), MB_OK);
		return;
	}

	//メッシュマテリアルの解放
	SAFE_DELETE_ARRAY(xFile->materials);

	//テクスチャの解放
	if (xFile->textures) {
		for (DWORD i = 0; i < xFile->materialNum; i++) {
			SAFE_RELEASE(xFile->textures[i]);
		}
		SAFE_DELETE_ARRAY(xFile->textures);
	}

	//メッシュの開放
	SAFE_RELEASE(xFile->mesh);
}

} // namespace
// EOF
