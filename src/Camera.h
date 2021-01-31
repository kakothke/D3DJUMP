#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// カメラ
class Camera
{
public:
	/// @name コンストラクタ
	//@{
	Camera();
	//@}

	/// @name 設定
	//@{
	void SetupWorldMatrix();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// カメラの位置
	D3DXVECTOR3 mEye;
	/// 注視点
	D3DXVECTOR3 mLookAt;
	/// カメラの上方向
	D3DXVECTOR3 mUpVec;
	//@}

};

} // namespace
// EOF
