#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
#include <math.h>

//-------------------------------------------------------------------------------------------------
namespace myGame {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param x 
/// @param y
/// @param z
Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{
}

//-------------------------------------------------------------------------------------------------
bool Vector3::operator ==(const Vector3& aVec) const
{
	if (x != aVec.x) {
		return false;
	}
	if (y != aVec.y) {
		return false;
	}
	if (z != aVec.z) {
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
bool Vector3::operator !=(const Vector3& aVec) const
{
	if (x == aVec.x) {
		return false;
	}
	if (y == aVec.y) {
		return false;
	}
	if (z == aVec.z) {
		return false;
	}
	return true;
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
void Vector3::operator +=(const Vector3& aVec)
{
	x += aVec.x;
	y += aVec.y;
	z += aVec.z;
}
void Vector3::operator -=(const Vector3& aVec)
{
	x -= aVec.x;
	y -= aVec.y;
	z -= aVec.z;
}
void Vector3::operator *=(const Vector3& aVec)
{
	x *= aVec.x;
	y *= aVec.y;
	z *= aVec.z;
}
void Vector3::operator /=(const Vector3& aVec)
{
	x /= aVec.x;
	y /= aVec.y;
	z /= aVec.z;
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
Vector3 Vector3::operator +(const Vector3& aVec) const
{
	return {
		x + aVec.x,
		y + aVec.y,
		z + aVec.z
	};
}
Vector3 Vector3::operator -(const Vector3& aVec) const
{
	return {
		x - aVec.x,
		y - aVec.y,
		z - aVec.z
	};
}
Vector3 Vector3::operator *(const Vector3& aVec) const
{
	return {
		x * aVec.x,
		y * aVec.y,
		z * aVec.z
	};
}
Vector3 Vector3::operator /(const Vector3& aVec) const
{
	return {
		x / aVec.x,
		y / aVec.y,
		z / aVec.z
	};
}

//-------------------------------------------------------------------------------------------------
/// �x�N�g���̒�����Ԃ�
float Vector3Math::Magnitude(Vector3 aVec)
{
	return (float)sqrt(pow(aVec.x, 2.0) + pow(aVec.y, 2.0) + pow(aVec.z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// ������1�ɕϊ������x�N�g����Ԃ�
Vector3 Vector3Math::Normalized(Vector3 aVec)
{
	float magnitude = Magnitude(aVec);
	return {
		aVec.x / magnitude,
		aVec.y / magnitude,
		aVec.z / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// D3DXVECTOR3�^�ɕϊ����ĕԂ�
const D3DXVECTOR3& Vector3Math::D3DXVECTOR3(Vector3 aVec)
{
	return {
		aVec.x,
		aVec.y,
		aVec.z
	};
}

} // namespace
// EOF
