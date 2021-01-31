#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <d3dx9.h>
#include "Transform.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// メッシュリスト
enum class MeshList
{
	TestMan,

	TERM
};

/// Xファイル構造体
struct XFile
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
	void draw(MeshList, Transform);
	bool load(MeshList);
	void release(MeshList);
	//@}

private:
	// @name 破棄（デストラクタ用）
	//@{
	void release(int aNum);
	//@}

	// @name プライベートメンバ変数
	//@{
	XFile mXFile[(int)MeshList::TERM];
	LPCTSTR mFilePath[(int)MeshList::TERM];
	//@}

	XFile* mTest;

};

} // namespace
// EOF
