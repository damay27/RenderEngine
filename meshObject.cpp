#include "stdafx.h"
#include "meshObject.h"


meshObject::meshObject() :Object(Vector3D(0, 0, 0), Material()), triangles()
{

}

meshObject::meshObject(const Vector3D &centerPositionIn, const Material &materialIn, vector<Triangle> trianglesIn) : Object(centerPositionIn, materialIn), triangles(trianglesIn)
{
}


meshObject::~meshObject()
{
}


vector<Triangle> meshObject::getTriangles()const {
	return triangles;
}

void meshObject::setTriangles(vector<Triangle> inputTriangles) {
	triangles = inputTriangles;
}

void meshObject::addTriangle(Triangle triangle) {
	triangles.push_back(triangle);
}

Triangle meshObject::getTriangle(int index)const {
	return triangles.at(index);
}

void meshObject::removeTriangle(int index) {
	triangles.erase(triangles.begin() + index);
}

void meshObject::removeTriangles(int from, int to) {
	triangles.erase(triangles.begin() + from, triangles.begin() + to);
}

int meshObject::numberOfTriangles()const {
	return int(triangles.size());
}


contactData meshObject::lineIntersection(const Vector3D &lineOrigin, const Vector3D &lineDirection)const {
	
	int numberTriangles = int(triangles.size());

	float closetsDistance = pow(10,100);
	contactData closestContact;

	for (int triangleIndex = 0; triangleIndex < numberTriangles; triangleIndex++){
		Triangle triangle = triangles[triangleIndex];

		Vector3D normal = triangle.getNormal();

		Vector3D planePoint = triangle.getVertex(0);

		if (Dot(normal, lineDirection) == 0) {//no intersetion with the plane return an empty vector
			continue;
		}
		else {//else find the intersection point
			float Term0 = normal.getX() * (planePoint.getX() - lineOrigin.getX());
			float Term1 = normal.getY() * (planePoint.getY() - lineOrigin.getY());
			float Term2 = normal.getZ() * (planePoint.getZ() - lineOrigin.getZ());
			float Denominator = lineDirection.getX() * normal.getX() + lineDirection.getY() * normal.getY() + lineDirection.getZ() * normal.getZ();
			float t = (Term0 + Term1 + Term2) / Denominator;


			float x = lineOrigin.getX() + lineDirection.getX() * t;
			float y = lineOrigin.getY() + lineDirection.getY() * t;
			float z = lineOrigin.getZ() + lineDirection.getZ() * t;
			Vector3D contactPoint(x, y, z);

			//check if the contact point is in the correct direction (in front of the camera instead of behiend)
			//by checking if t is positive
			if (t < 0) {
				continue;
			}

			//check if it is actualy on the triangle
			if (triangle.isOnTriangle(contactPoint) == false) {
				continue;
			}

			if (lineOrigin.distance(contactPoint) > closetsDistance) {
				continue;
			}

			if (triangle.isOnTriangle(lineOrigin) && closestContact.getContactType() != GOOD_CONTACT) {//if the ray is being cast from the surface of a triangle make sure to exclude the intersection with that triangle
				closestContact = contactData(contactPoint, normal, this->getMaterial(), SELF_INTERSECT);
			}
			else {

				closestContact = contactData(contactPoint, normal, this->getMaterial(), GOOD_CONTACT);
				closetsDistance = lineOrigin.distance(contactPoint);
			}

		}

	}

	return closestContact;

}