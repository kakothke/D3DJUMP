#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Camera::Camera()
{
	mEye = D3DXVECTOR3(0, 20, 0);
	mLookAt = D3DXVECTOR3(0, 0, 0);
	mUpVec = D3DXVECTOR3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// カメラの設定
void Camera::SetupWorldMatrix()
{
	// 視界
	D3DXMATRIXA16 matView;

	D3DXMatrixLookAtLH(&matView, &mEye, &mLookAt, &mUpVec);

	// 投影行列を設定。
	// 視野角、アスペクト比、視覚クリッピング用の最接近距離と最遠方距離の四つが必要。
	D3DXMATRIXA16 matProj;

	FLOAT tmpAspect = (float)Direct3D9::getInst()->params().BackBufferWidth / (float)Direct3D9::getInst()->params().BackBufferHeight;

	D3DXMatrixPerspectiveFovLH(
		&matProj,
		// 視野角
		D3DX_PI / 4,
		// アスペクト比
		tmpAspect,
		// 最近接距離
		1.0f,
		// 最遠方距離
		800.0f
	);

	// ビューマトリクスの設定
	Direct3D9::getInst()->device()->SetTransform(D3DTS_VIEW, &matView);

	//ディバイスに対して、投影行列を設定。
	Direct3D9::getInst()->device()->SetTransform(D3DTS_PROJECTION, &matProj);
}

} // namespace
// EOF
