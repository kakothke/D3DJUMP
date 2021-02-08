#pragma once

//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// �J����
class Camera : public GameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	Camera();
	Camera(Transform aTransform);
	Camera(float aZoom);
	Camera(Transform aTransform, float aZoom);
	//@}
	
	/// @name �X�V/�`��
	//@{
	virtual void update() override;
	virtual void draw() const override {}
	//@}

protected:
	/// @name ���������֐�
	//@{
	/// �ˉe
	void setViewMatrix();
	/// �w�肵���ʒu������
	void lookAt(Vector3 aPos);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �����_
	Vector3 mLookPos;
	// / ����p
	float mZoom;
	/// ������
	bool mIslookAt;
	//@}

};

} // namespace
// EOF
