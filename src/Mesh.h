#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <d3dx9.h>
#include "Singleton.h"
#include "MeshList.h"
#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// メッシュ（Xファイルを使用）
class Mesh : public Singleton<Mesh>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Mesh();
	~Mesh();
	//@}

	/// @name 初期化処理
	//@{
	void initialize();
	//@}

	/// @name 描画/読み込み/破棄
	//@{
	bool draw(MeshList, Transform);
	bool load(MeshList);
	void release(MeshList);
	//@}

private:
	/// @name 内部構造体
	//@{
	/// Xファイル構造体
	struct XFileData
	{
		/// メッシュマテリアル
		D3DMATERIAL9* materials;
		/// テクスチャデータ
		LPDIRECT3DTEXTURE9* textures;
		/// メッシュ
		LPD3DXMESH mesh;
		/// メッシュ数
		DWORD materialNum;
	};
	//@}

	// @name 破棄（デストラクタ用）
	//@{
	void release(int aNum);
	//@}

	// @name プライベートメンバ変数
	//@{
	XFileData mXFile[(int)MeshList::TERM];
	LPCTSTR mFilePath[(int)MeshList::TERM];
	//@}

	XFileData* mTest;

};

} // namespace
// EOF
