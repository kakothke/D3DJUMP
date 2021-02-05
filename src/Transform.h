#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"
#include "d3dx9.h"
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// オブジェクトの位置、回転、スケールを扱うクラス
class Transform
{
public:
	/// @name コンストラクタ
	//@{
	Transform();
	Transform(Vector3 aPos, Vector3 aRot, Vector3 aScale);
	//@}

	/// @name メンバ変数
	//@{
	/// 位置
	Vector3 pos;
	/// 回転
	Vector3 rot;
	/// スケール
	Vector3 scale;
	//@}

};

} // namespace
// EOF
