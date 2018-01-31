#pragma once
#include "Object.h"
#include "triangle.hpp"

#include <vector>

class meshObject :
	public Object
{
public:
	meshObject();
	meshObject(const Vector3D &centerPosition, const Material &material, vector<Triangle> triangles);
	~meshObject();


	vector<Triangle> getTriangles()const;
	void setTriangles(vector<Triangle> inputTriangles);
	void addTriangle(Triangle);
	Triangle getTriangle(int)const;
	void removeTriangle(int);//indexed from zero
	void removeTriangles(int, int);//indexed from zero
	int numberOfTriangles()const;


	virtual contactData lineIntersection(const Vector3D &lineOrigin, const Vector3D &lineDirection)const;

private:
	vector<Triangle> triangles;
};

