#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// 3�����x�N�g��
class Vector3
{
public:
    /// @name �R���X�g���N�^
    //@{
    Vector3();
    Vector3(float aX, float aY, float aZ);
    //@}

    /// @name �x�N�g���ϊ��֐�
    //@{
    /// �x�N�g���̒���
    float magnitude() const;
    /// �����͂��̂܂܂Œ�����1�̃x�N�g����Ԃ�
    Vector3 normalized() const;
    //@}

    /// @name D3DXVECTOR3�^�ɕϊ����ĕԂ�
    //@{
    const D3DXVECTOR3& d3dxVector3();
    //@}

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    void operator +=(float aNum);
    void operator -=(float aNum);
    void operator *=(float aNum);
    void operator /=(float aNum);

    void operator +=(const Vector3& aVector3);
    void operator -=(const Vector3& aVector3);
    void operator *=(const Vector3& aVector3);
    void operator /=(const Vector3& aVector3);

    Vector3 operator -() const;

    Vector3 operator +(float aNum) const;
    Vector3 operator -(float aNum) const;
    Vector3 operator *(float aNum) const;
    Vector3 operator /(float aNum) const;

    Vector3 operator +(const Vector3& aVector3) const;
    Vector3 operator -(const Vector3& aVector3) const;
    Vector3 operator *(const Vector3& aVector3) const;
    Vector3 operator /(const Vector3& aVector3) const;
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    float z;
    //@}

};

} // namespace
// EOF
