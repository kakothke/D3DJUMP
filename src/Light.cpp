#include "Light.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Light::Light() : GameObject(Tag::Light)
{
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
Light::Light(LPDIRECT3DDEVICE9 aDevice,Transform aTransform) : GameObject(aTransform, Tag::Light)
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
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &mTransform.pos.d3dxVector3());
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Light::draw() const
{
	Direct3D9::getInst()->device()->SetLight(0, &mLight);
}

} // namespace
// EOF