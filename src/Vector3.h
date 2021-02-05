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
    Vector3(float aX, float aY, float aZ);
    //@}

    /// @ name 演算子オーバーロード
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
    static float Magnitude(Vector3 aVec);
    /// 長さを1に変換したベクトルを返す
    static Vector3 Normalized(Vector3 aVec);
    /// D3DXVECTOR3型に変換して返す
    static const D3DXVECTOR3& D3DXVECTOR3(Vector3 aVec);
    //@}

private:
    Vector3Math();

};

} // namespace
// EOF
