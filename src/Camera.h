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
	Camera(D3DXVECTOR3, D3DXVECTOR3);
	//@}
	
	/// @name 更新
	//@{
	void update();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	D3DXVECTOR3 mCameraPos;
	D3DXVECTOR3 mLookPos;
	//@}

};

} // namespace
// EOF
