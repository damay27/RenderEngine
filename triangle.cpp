#include "stdafx.h"
#include "Triangle.hpp"
#include "VectorMath.h"

Triangle::Triangle(Vector3D p0, Vector3D p1, Vector3D p2): v0(p0), v1(p1), v2(p2){
	computeNormal();
}

Triangle::Triangle(const Triangle &copyTriangle){
	v0 = copyTriangle.getVertex0();
	v1 = copyTriangle.getVertex1();
	v2 = copyTriangle.getVertex2();
	normal = copyTriangle.getNormal();
}

Triangle::Triangle():v0(), v1(), v2() {

}


Vector3D Triangle::getVertex0()const {
	return v0;
}


Vector3D Triangle::getVertex1()const {
	return v1;
}


Vector3D Triangle::getVertex2()const {
	return v2;
}


void Triangle::setVertex(int vertexNum, const Vector3D &val) {//valid vertex numbers are 0 through 2
	switch (vertexNum) {
	case 0:
		v0 = val;
		break;
	case 1:
		v1 = val;
		break;
	case 2:
		v2 = val;
		break;
	default:
		//probably should throw an exception here :)
		std::cout << "ERROR: Vertex number not in range 0 to 2." << std::endl;
	}

	computeNormal();
}

Vector3D Triangle::getNormal()const {
	return normal;
}


/*
this is a private helper function that computes the normal using vertex zero as the common vertex
between the two vectos. It is called at the end of the constructor and any function that changes the vertices 
so that the normal is always up to date. 
*/
void Triangle::computeNormal() {
	Vector3D v0v1 = v1 - v0;
	Vector3D v0v2 = v2 - v0;
	normal = Cross(v0v1, v0v2);
}
