#pragma once

#include <string>
using namespace std;

class Vector3D
{
public:
	Vector3D();
	~Vector3D();
	Vector3D(float, float, float);
	Vector3D(const Vector3D &v);

	void operator=(const Vector3D &v);

	bool isNull() const;
	void setIsNull(bool);

	float getX() const;
	float getY() const;
	float getZ() const;

	void setX(float);
	void setY(float);
	void setZ(float);
	void setAll(float, float, float);

	Vector3D operator+(const Vector3D &v);
	Vector3D operator-(const Vector3D &v);

	float distance(const Vector3D &point);
	float magnitude();
	Vector3D normalize();
	string print();

private:
	float x, y, z;
	bool IsNull;

};

float Dot(const Vector3D &a, const Vector3D &b);

Vector3D Cross(const Vector3D &a, const Vector3D &b);
