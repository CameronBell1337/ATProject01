#include "Vector3.h"
#include <cmath>

/**
 *   @brief   Constructor.
 *   @details Requires values for it's x and y magnitudes.
 *   @return  void
 */
Vector3::Vector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{}

/**
 *   @brief   Copies a vector.
 *   @details Constructs a new vector2 from an existing.
 *   @return  void
 */
Vector3::Vector3(const Vector3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}

/**
 *   @brief   Scales the vector.
 *   @details Uses a single scalar value to scale the vector.
 *   @return  void
 */
Vector3 Vector3::operator*(float sclr)
{
	Vector3 vector(*this);
	vector.x *= sclr;
	vector.y *= sclr;
	vector.z *= sclr;
	return vector;
}

Vector3 Vector3::operator+(const Vector3& op)
{
	Vector3 vector(*this);
	vector.x += op.x;
	vector.y += op.y;
	vector.z += op.z;
	return vector;
}

Vector3 Vector3::operator-(const Vector3& op)
{
	Vector3 vector(*this);
	vector.x -= op.x;
	vector.y -= op.y;
	vector.z -= op.z;
	return vector;
}

bool Vector3::operator==(const Vector3& op)
{
	return (x == op.x && y == op.y && z == op.z);
}

float Vector3::magnitude()
{
	return sqrtf((x * x) + (y * y));
}

void Vector3::normalise()
{
	auto mag = magnitude();

	if (!mag)
	{
		return;
	}

	x /= mag;
	y /= mag;
}