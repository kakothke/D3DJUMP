#include "Light.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Light::Light() : GameObject(GameObjectTag::Light)
{
	// 白のディレクショナルライトを設定する
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse.r = 1.0f;
	mLight.Diffuse.g = 1.0f;
	mLight.Diffuse.b = 1.0f;
	mLight.Diffuse.a = 0.0f;
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
Light::Light(Transform aTransform) : GameObject(aTransform, GameObjectTag::Light)
, mLight()
{
	// 白のディレクショナルライトを設定する
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse.r = 1.0f;
	mLight.Diffuse.g = 1.0f;
	mLight.Diffuse.b = 1.0f;
	mLight.Diffuse.a = 0.0f;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Light::update()
{
	mTransform.pos.x = sinf((float)timeGetTime() / 1000.0f);
	mTransform.pos.y = cosf((float)timeGetTime() / 1000.0f);
	mTransform.pos.z = 0;
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &Vector3Math::D3DXVECTOR3(mTransform.pos));
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Light::draw() const
{
	Direct3D9::getInst()->device()->SetLight(0, &mLight);
}

} // namespace
// EOF
