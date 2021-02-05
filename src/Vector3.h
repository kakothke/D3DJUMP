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

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    bool operator ==(const Vector3& aVec) const;
    bool operator !=(const Vector3& aVec) const;

    void operator +=(float aNum);
    void operator -=(float aNum);
    void operator *=(float aNum);
    void operator /=(float aNum);

    void operator +=(const Vector3& aVec);
    void operator -=(const Vector3& aVec);
    void operator *=(const Vector3& aVec);
    void operator /=(const Vector3& aVec);

    Vector3 operator -() const;

    Vector3 operator +(float aNum) const;
    Vector3 operator -(float aNum) const;
    Vector3 operator *(float aNum) const;
    Vector3 operator /(float aNum) const;

    Vector3 operator +(const Vector3& aVec) const;
    Vector3 operator -(const Vector3& aVec) const;
    Vector3 operator *(const Vector3& aVec) const;
    Vector3 operator /(const Vector3& aVec) const;
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    float z;
    //@}

};

/// �x�N�g���̌v�Z
class Vector3Math
{
public:
    //@ name �ϊ��֐�
    //@{
    /// �x�N�g���̒�����Ԃ�
    static float Magnitude(Vector3 aVec);
    /// ������1�ɕϊ������x�N�g����Ԃ�
    static Vector3 Normalized(Vector3 aVec);
    /// D3DXVECTOR3�^�ɕϊ����ĕԂ�
    static const D3DXVECTOR3& D3DXVECTOR3(Vector3 aVec);
    //@}

private:
    Vector3Math();

};

} // namespace
// EOF
