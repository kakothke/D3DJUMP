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

    /// @name ベクトル変換関数
    //@{
    /// ベクトルの長さ
    float magnitude() const;
    /// 方向はそのままで長さが1のベクトルを返す
    Vector3 normalized() const;
    //@}

    /// @name D3DXVECTOR3型に変換して返す
    //@{
    const D3DXVECTOR3& d3dxVector3();
    //@}

    /// @ name 演算子オーバーロード
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

    /// @name メンバ変数
    //@{
    float x;
    float y;
    float z;
    //@}

};

} // namespace
// EOF
