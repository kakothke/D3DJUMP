#pragma once

//-------------------------------------------------------------------------------------------------
#include "d3dx9.h"

//-------------------------------------------------------------------------------------------------
namespace myGame {

/// 3次元ベクトル
class Vector3
{
public:
    /// @name コンストラクタ
    //@{
    Vector3();
    Vector3(float x, float y, float z);
    //@}

    /// @ name 演算子オーバーロード
    //@{
    Vector3 operator -() const;
    Vector3 operator +(float aValue) const;
    Vector3 operator -(float aValue) const;
    Vector3 operator *(float aValue) const;
    Vector3 operator /(float aValue) const;
    Vector3 operator +(const Vector3& aVector) const;
    Vector3 operator -(const Vector3& aVector) const;
    Vector3 operator *(const Vector3& aVector) const;
    Vector3 operator /(const Vector3& aVector) const;

    bool operator ==(const Vector3& aVector) const;
    bool operator !=(const Vector3& aVector) const;

    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Vector3& aVector);
    void operator -=(const Vector3& aVector);
    void operator *=(const Vector3& aVector);
    void operator /=(const Vector3& aVector);
    //@}

    /// @name メンバ変数
    //@{
    float x;
    float y;
    float z;
    //@}

};

/// ベクトルの計算
class Vector3Math
{
public:
    //@ name 変換関数
    //@{
    /// ベクトルの長さを返す
    static float Magnitude(Vector3 aVector);
    /// 長さを1に変換したベクトルを返す
    static Vector3 Normalized(Vector3 aVector);
    /// D3DXVECTOR3型に変換して返す
    static const D3DXVECTOR3& D3DXVECTOR3(Vector3 aVector);
    //@}

private:
    Vector3Math();

};

} // namespace
// EOF
