#pragma once

#include "Vector3D.h"
#include <iostream>
using namespace std;



class Triangle {

public:
	Triangle(Vector3D, Vector3D, Vector3D);
	Triangle();
	Triangle(const Triangle &copy);
	Vector3D getVertex0()const;
	Vector3D getVertex1()const;
	Vector3D getVertex2()const;
	void setVertex(int vertexNum, const Vector3D &val);
	Vector3D getNormal()const;
	
private:
	Vector3D v0, v1, v2, normal;

	void computeNormal();


};