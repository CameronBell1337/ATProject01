#pragma once
class Vector3
{
public:
	//Referenced from James Huxtable's ASGE Engine//


	//constructors 
	Vector3() = default;
	~Vector3() = default;
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& rhs);


	//operations
	Vector3 operator*(float sclr);
	Vector3 operator+(const Vector3& op);
	Vector3 operator-(const Vector3& op);

	Vector3& operator=(const Vector3& rhs) = default;

	bool operator==(const Vector3& op);

	void normalise();
	float magnitude();
	
	

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

};