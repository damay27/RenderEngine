#pragma once
#include "Vector3D.h"
#include "triangle.hpp"
#include "Object.h"
#include <string>

class Transform3D
{
public:
	Transform3D();
	~Transform3D();
	void scale(float, float, float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void translate(float, float, float);
	Vector3D applyTransform(const Vector3D &center, const Vector3D &point);
	Triangle applyTransform(const Vector3D &centerPoint, const Triangle &triangle);
	Object applyTransform(const Vector3D &centerPoint, const Object &object);
	string print();

private:
	float matrix[3][3];//this stores the scale and rotation matrix
	float transX, transY, transZ;

	void multiplyMatrix(const float (&inputArray)[3][3]);


};

