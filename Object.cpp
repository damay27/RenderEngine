#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}


Object::Object(const vector<Triangle> &triangleVector, const Vector3D &centerPosition, const Material &objectMaterial): triangles(triangleVector),center(centerPosition), material(objectMaterial){

}

vector<Triangle> Object::getTriangles()const {
	return triangles;
}

void Object::setTriangles(vector<Triangle> inputTriangles) {
	triangles = inputTriangles;
}

void Object::addTriangle(Triangle triangle) {
	triangles.push_back(triangle);
}

Triangle Object::getTriangle(int index)const {
	return triangles.at(index);
}

void Object::removeTriangle(int index) {
	triangles.erase(triangles.begin()+index);
}

void Object::removeTriangles(int from, int to) {
	triangles.erase(triangles.begin() + from, triangles.begin() + to);
}

int Object::numberOfTriangles()const {
	return int(triangles.size());
}

Material Object::getMaterial()const {
	return material;
}


void Object::setMaterial(const Material &material) {
	this->material = material;
}
