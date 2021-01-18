#include "TestPlane.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
TestPlane::TestPlane()
{
	mTransform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mTransform.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mTransform.modelType = 0;

	mTheModels.mesh = NULL;				// システム中のメッシュオブジェクト
	mTheModels.meshMaterials = NULL;		// メッシュの質感(materials)
	mTheModels.meshTextures = NULL;		// メッシュの質感(materials)
	mTheModels.materialNum = 0;		// メッシュ質感の数

	mFileName = TEXT("res/models/f-mine.x");

	if (!LoadModelsFromXFile()) {
		MessageBox(NULL, TEXT("モデルの読み込みに失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// デストラクタ
/// </summary>
TestPlane::~TestPlane()
{
}
//-------------------------------------------------------------------------------------------------
/// <summary>
/// 描画
/// </summary>
void TestPlane::Render() const
{
}

//-------------------------------------------------------------------------------------------------
/// <summary>
/// データのロード
/// </summary>
bool TestPlane::LoadModelsFromXFile()
{
	LPD3DXBUFFER pD3DXMtrlBuf;

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(mFileName, D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL, &pD3DXMtrlBuf, NULL, &mTheModels.materialNum, &mTheModels.mesh))) {
		MessageBox(NULL, TEXT("Xファイルが見つかりませんでした。"), Define::WindowName, MB_OK);
		return false;
	}

	// pD3DXMtrlBufから、マテリアルやテクスチャの名称などの情報を取得する。
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuf->GetBufferPointer();
	mTheModels.meshMaterials = new D3DMATERIAL9[mTheModels.materialNum];
	mTheModels.meshTextures = new LPDIRECT3DTEXTURE9[mTheModels.materialNum];

	for (DWORD i0 = 0; i0 < mTheModels.materialNum; i0++) {
		// 質感（material）のコピー
		mTheModels.meshMaterials[i0] = d3dxMaterials[i0].MatD3D;

		// 質感（material）に環境光を設定する（D3DXが何もしないため）
		mTheModels.meshMaterials[i0].Ambient = mTheModels.meshMaterials[i0].Diffuse;

		mTheModels.meshTextures[i0] = NULL;
		if (d3dxMaterials[i0].pTextureFilename != NULL) {
			if (FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, (LPCWSTR)d3dxMaterials[i0].pTextureFilename, &(mTheModels.meshTextures[i0])))) {
				MessageBox(NULL, TEXT("Xファイルで指定されたテクスチャマップファイルが見つかりませんでした。"), Define::WindowName, MB_OK);
				return(E_FAIL);
			}
		}
	}

	// 質感（material）バッファの開放。
	pD3DXMtrlBuf->Release();
	pD3DXMtrlBuf = NULL;

	return true;
}

} // namespace
