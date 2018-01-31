#include "stdafx.h"
#include "Vector3D.h"


Vector3D::Vector3D(): x(0), y(0), z(0), IsNull(true)
{
}

Vector3D::Vector3D(float a, float b, float c) : x(a), y(b), z(c), IsNull(false)
{

}

Vector3D::~Vector3D()
{
}

Vector3D::Vector3D(const Vector3D &v){
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
	this->IsNull = v.isNull();
}

void Vector3D::operator=(const Vector3D &v) {
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
	this->IsNull = v.isNull();
}

bool Vector3D::isNull() const {
	return IsNull;
}

void Vector3D::setIsNull(bool val) {
	IsNull = val;
}

float Vector3D::getX() const {
	return x;
}

float Vector3D::getY() const {
	return y;
}

float Vector3D::getZ() const {
	return z;
}

void Vector3D::setX(float a) {
	x = a;
}

void Vector3D::setY(float a) {
	y = a;
}

void Vector3D::setZ(float a) {
	z = a;
}

void Vector3D::setAll(float xIn, float yIn, float zIn) {
	x = xIn;
	y = yIn;
	z = zIn;
}


float Vector3D::distance(const Vector3D &point) {//finds cartesian distance between two points
	Vector3D distanceVector = *this - point;//need to dereferance pointer to use the subtraction operator

	float xtemp = pow(distanceVector.getX(), 2);
	float ytemp = pow(distanceVector.getY(), 2);
	float ztemp = pow(distanceVector.getZ(), 2);

	return(sqrt(xtemp + ytemp + ztemp));
}


float Vector3D::magnitude() {//finds the magnitude of the vector
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}


Vector3D Vector3D::normalize() {//returns a copy of the vector that has the same direction but has a magnitude of 1
	float mag = this->magnitude();

	float xtemp = x / mag;
	float ytemp = y / mag;
	float ztemp = z / mag;

	return Vector3D(xtemp, ytemp, ztemp);
}


string Vector3D::print() {
	return ( "<" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ">" );
}

Vector3D Vector3D::operator+(const Vector3D &v) {
	return Vector3D(this->x - v.getX(), this->y - v.getY(), this->z - v.getZ());
}


Vector3D Vector3D::operator-(const Vector3D &v) {
	return Vector3D(this->x - v.getX(), this->y - v.getY(), this->z - v.getZ());
}

float Dot(const Vector3D &a, const Vector3D &b) {
	return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ();
}

Vector3D Cross(const Vector3D &a, const Vector3D &b) {
	float term1 = a.getY()*b.getZ() - b.getY()*a.getZ();
	float term2 = -(a.getX()*b.getZ() - b.getX()*a.getZ());
	float term3 = a.getX()*b.getY() - b.getX()*a.getY();
	return Vector3D(term1, term2, term3);
}
