#pragma once

#include <vector>
#include "triangle.hpp"
#include "Vector3D.h"
#include "Material.h"


class Object
{
public:
	Object();
	~Object();
	Object(const vector<Triangle> &triangleVector, const Vector3D &centerPosition, const Material &objectMaterial);

	vector<Triangle> getTriangles()const;
	void setTriangles(vector<Triangle> inputTriangles);
	void addTriangle(Triangle);
	Triangle getTriangle(int)const ;
	void removeTriangle(int);//indexed from zero
	void removeTriangles(int, int);//indexed from zero
	int numberOfTriangles()const;
	Material getMaterial()const;
	void setMaterial(const Material &material);
	


private:
	Vector3D center;
	vector<Triangle> triangles;
	Material material;

};

