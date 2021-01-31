#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
#include <math.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param x 
/// @param y
/// @param z
Vector3::Vector3(float aX, float aY, float aZ)
	: x(aX)
	, y(aY)
	, z(aZ)
{
}

//-------------------------------------------------------------------------------------------------
/// ベクトルの長さ
float Vector3::magnitude() const
{
	return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//-------------------------------------------------------------------------------------------------
/// 方向はそのままで長さが1のベクトルを返す
Vector3 Vector3::normalized() const
{
	return {
		x / magnitude(),
		y / magnitude(),
		z / magnitude()
	};
}

//-------------------------------------------------------------------------------------------------
/// D3DXVECTOR3型に変換して返す
const D3DXVECTOR3& Vector3::d3dxVector3()
{
	return {
		x,
		y,
		z
	};
}

//-------------------------------------------------------------------------------------------------
void Vector3::operator +=(float aNum)
{
	x += aNum;
	y += aNum;
	z += aNum;
}
void Vector3::operator -=(float aNum)
{
	x -= aNum;
	y -= aNum;
	z -= aNum;
}
void Vector3::operator *=(float aNum)
{
	x *= aNum;
	y *= aNum;
	z *= aNum;
}
void Vector3::operator /=(float aNum)
{
	x /= aNum;
	y /= aNum;
	z /= aNum;
}

//-------------------------------------------------------------------------------------------------
void Vector3::operator +=(const Vector3& aVector3)
{
	x += aVector3.x;
	y += aVector3.y;
	z += aVector3.z;
}
void Vector3::operator -=(const Vector3& aVector3)
{
	x -= aVector3.x;
	y -= aVector3.y;
	z -= aVector3.z;
}
void Vector3::operator *=(const Vector3& aVector3)
{
	x *= aVector3.x;
	y *= aVector3.y;
	z *= aVector3.z;
}
void Vector3::operator /=(const Vector3& aVector3)
{
	x /= aVector3.x;
	y /= aVector3.y;
	z /= aVector3.z;
}

//-------------------------------------------------------------------------------------------------
Vector3 Vector3::operator-() const
{
	return {
		-x,
		-y,
		-z
	};
}

//-------------------------------------------------------------------------------------------------
Vector3 Vector3::operator +(float aNum) const
{
	return {
		x + aNum,
		y + aNum,
		z + aNum
	};
}
Vector3 Vector3::operator -(float aNum) const
{
	return {
		x - aNum,
		y - aNum,
		z - aNum
	};
}
Vector3 Vector3::operator *(float aNum) const
{
	return {
		x * aNum,
		y * aNum,
		z * aNum
	};
}
Vector3 Vector3::operator /(float aNum) const
{
	return {
		x / aNum,
		y / aNum,
		z / aNum
	};
}

//-------------------------------------------------------------------------------------------------
Vector3 Vector3::operator +(const Vector3& aVector3) const
{
	return {
		x + aVector3.x,
		y + aVector3.y,
		z + aVector3.z
	};
}
Vector3 Vector3::operator -(const Vector3& aVector3) const
{
	return {
		x - aVector3.x,
		y - aVector3.y,
		z - aVector3.z
	};
}
Vector3 Vector3::operator *(const Vector3& aVector3) const
{
	return {
		x * aVector3.x,
		y * aVector3.y,
		z * aVector3.z
	};
}
Vector3 Vector3::operator /(const Vector3& aVector3) const
{
	return {
		x / aVector3.x,
		y / aVector3.y,
		z / aVector3.z
	};
}

} // namespace
// EOF
