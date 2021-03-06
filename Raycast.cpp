#include "stdafx.h"
#include "Raycast.h"
#include  "Triangle.hpp"
#include "Vector3D.h"


/*
This function determines if a given point is on the face of a triangle by taking the cross product of the
vectors formed by the each leg of the triangle and a vertex and the given point. If the resulting vector points in the 
same direction as the normal for each cross product then the point is on the triangle
*/
bool isOnTriangle(Triangle triangle, Vector3D point) {
	//vector from v0 to v1
	Vector3D cross;
	Vector3D normal = triangle.getNormal();

	//vector from v0 to v1
	Vector3D v1_v0 = triangle.getVertex1() - triangle.getVertex0();
	Vector3D point_v0 = point - triangle.getVertex0();
	cross = Cross(v1_v0, point_v0);
	if (Dot(cross, normal) < 0) {
		return false;
	}

	//vector from v1 to v1
	Vector3D v2_v1 = triangle.getVertex2() - triangle.getVertex1();
	Vector3D point_v1 = point - triangle.getVertex1();
	cross = Cross(v2_v1, point_v1);
	if (Dot(cross, normal) < 0) {
		return false;
	}

	//vector from v0 to v1
	Vector3D v0_v2 = triangle.getVertex0() - triangle.getVertex2();
	Vector3D point_v2 = point - triangle.getVertex2();
	cross = Cross(v0_v2, point_v2);
	if (Dot(cross, normal) < 0) {
		return false;
	}

	return true;
}

/*
This function tests if a ray fired using the input point and direction hits the triangle. 
If it does the 3D point is returned. If not the the returned Vector3d object is null. 
*/
Vector3D Raycast(Vector3D originPoint, Vector3D direction, Triangle triangle) {

	Vector3D triangleNormal = triangle.getNormal();
	Vector3D planePoint = triangle.getVertex0();

	if (Dot(triangleNormal, direction) == 0) {//no intersetion with the plane return an empty vector
		return(Vector3D());
	}
	else {//else find the intersection point
		float Term0 = triangleNormal.getX() * (planePoint.getX() - originPoint.getX());
		float Term1 = triangleNormal.getY() * (planePoint.getY() - originPoint.getY());
		float Term2 = triangleNormal.getZ() * (planePoint.getZ() - originPoint.getZ());
		float Denominator = direction.getX() * triangleNormal.getX() + direction.getY() * triangleNormal.getY() + direction.getZ() * triangleNormal.getZ();
		float t = (Term0 + Term1 + Term2) / Denominator;


		float x = originPoint.getX() + direction.getX() * t;
		float y = originPoint.getY() + direction.getY() * t;
		float z = originPoint.getZ() + direction.getZ() * t;
		Vector3D contactPoint(x, y, z);

		//check if the contact point is in the correct direction (in front of the camera instead of behiend)
		//by checking if t is positive
		if (t<0) {
			return(Vector3D());
		}

		//check if it is actualy on the triangle
		if (isOnTriangle(triangle, contactPoint) == false) {
			return(Vector3D());
		}
		return contactPoint;
	}

}
