#include "Light.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Light::Light() : GameObject(GameObjectTag::Light)
{
	// ���̃f�B���N�V���i�����C�g��ݒ肷��
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse.r = 1.0f;
	mLight.Diffuse.g = 1.0f;
	mLight.Diffuse.b = 1.0f;
	mLight.Diffuse.a = 0.0f;
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
Light::Light(Transform aTransform) : GameObject(aTransform, GameObjectTag::Light)
, mLight()
{
	// ���̃f�B���N�V���i�����C�g��ݒ肷��
	ZeroMemory(&mLight, sizeof(D3DLIGHT9));
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse.r = 1.0f;
	mLight.Diffuse.g = 1.0f;
	mLight.Diffuse.b = 1.0f;
	mLight.Diffuse.a = 0.0f;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Light::update()
{
	mTransform.pos.x = sinf((float)timeGetTime() / 1000.0f);
	mTransform.pos.y = cosf((float)timeGetTime() / 1000.0f);
	mTransform.pos.z = 0;
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &Vector3Math::D3DXVECTOR3(mTransform.pos));
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Light::draw() const
{
	Direct3D9::getInst()->device()->SetLight(0, &mLight);
}

} // namespace
// EOF
