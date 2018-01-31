#include "stdafx.h"
#include "Transform3D.h"
#include <algorithm> 

#define PI 3.14159265f
#define deg2rad PI/180.0f


Transform3D::Transform3D() : transX(0), transY(0), transZ(0)
{
	//Set each element of the matrix to zero
	for (int row = 0; row < 3; row++) {
		for(int col=0; col<3; col++)
			matrix[row][col] = 0;
	}
	
	//Then insert ones diagonally from the top left to the bottom right
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[2][2] = 1;
}


Transform3D::~Transform3D()
{
}

//This function populates a scale matrix with the given parameters and multiplies it by the matrix member variable
void Transform3D::scale(float x, float y, float z) {
	float scaleArray[3] = { x, y, z };

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++)
			matrix[row][col] = matrix[row][col] * scaleArray[row];
	}

}

/*
The rotation functions create the needed rotation matrix for the specified andgle and axis and then mutiply 
this matrix by the matrix member variable
*/
void Transform3D::rotateX(float theta) {
	float rotArray[3][3] = 
	{
		{1, 0, 0}, 
		{0, cos(theta*deg2rad), -sin(theta*deg2rad)}, 
		{0, sin(theta*deg2rad), cos(theta*deg2rad)}
	};

	multiplyMatrix(rotArray);
}


void Transform3D::rotateY(float theta) {
	float rotArray[3][3] =
	{
		{ cos(theta*deg2rad), 0, sin(theta*deg2rad) },
		{ 0, 1, 0 },
		{ -sin(theta*deg2rad), 0, cos(theta*deg2rad) }
	};

	multiplyMatrix(rotArray);
}


void Transform3D::rotateZ(float theta) {
	float rotArray[3][3] =
	{
		{ cos(theta*deg2rad), -sin(theta*deg2rad), 0},
		{ sin(theta*deg2rad), cos(theta*deg2rad), 0 },
		{ 0, 0, 1 }
	};

	multiplyMatrix(rotArray);
}

//This function adds the specified amount of translation to the translation variables 
void Transform3D::translate(float x, float y, float z) {
	transX += x;
	transY += y;
	transZ += z;
}

/*
This function workes by taking a point and apply the transformation on it around a given center point
*/
Vector3D Transform3D::applyTransform(const Vector3D &center, const Vector3D &point) {
	float centerX = center.getX();
	float centerY = center.getY();
	float centerZ = center.getZ();

	/*
	The point needs to be moved so that its center is at the origin so that the scale and rotation will be
	applied correctly. It will be added back in later. This is because all the matrix operations for rotation and scale
	all work relative to the origin. (If the "center" is at the center of the mesh
	then this step will move the mesh back to the position (0, 0, 0)
	*/
	float x = point.getX() - centerX;
	float y = point.getY() - centerY;
	float z = point.getZ() - centerZ;

	//Apply the matrix multiplication for a vector and add the translation. Finally add the center back in. 
	float newX = (matrix[0][0] * x) + (matrix[0][1] * y) + (matrix[0][2] * z) + transX + centerX;
	float newY = (matrix[1][0] * x) + (matrix[1][1] * y) + (matrix[1][2] * z) + transY + centerY;
	float newZ = (matrix[2][0] * x) + (matrix[2][1] * y) + (matrix[2][2] * z) + transZ + centerZ;

	return Vector3D(newX, newY, newZ);
}

//To apply the transform to a triangle apply the transform at each vertex
Triangle Transform3D::applyTransform(const Vector3D &centerPoint, const Triangle &triangle) {

	Vector3D v0New = applyTransform(centerPoint, triangle.getVertex0());
	Vector3D v1New = applyTransform(centerPoint, triangle.getVertex1());
	Vector3D v2New = applyTransform(centerPoint, triangle.getVertex2());

	return Triangle(v0New, v1New, v2New);
}

//To apply the transform to an object apply the transform to each triangle
Object Transform3D::applyTransform(const Vector3D &centerPoint, const Object &object) {
	Object resultObject;
	vector<Triangle> triangles = object.getTriangles();

	for (int i = 0; i < triangles.size(); i++) {
		Triangle temp = applyTransform(centerPoint, triangles.at(i));
		resultObject.addTriangle(temp);
	}

	return resultObject;
}


//This is a helper function to show the values in the transform matrix
string Transform3D::print() {
	string returnString;

	for (int row = 0; row < 3; row++) {
		returnString += "| ";
			for (int col = 0; col < 3; col++) {
				returnString += to_string(matrix[row][col]) + ", ";
			}

			returnString += " |\n";
	}

	return returnString;
}

//This function implements matrix multiplication for a matrix times another matrix
void Transform3D::multiplyMatrix(const float(&inputArray)[3][3]) {

	float outMatrix[3][3];

	for (int inputRow = 0; inputRow < 3; inputRow++) {//get a row from the input matrix

		for (int matCol = 0; matCol < 3; matCol++) {//get a column from the scale rotation matrix
			float sum = 0;
			for (int i = 0; i < 3; i++) {//loop through each element of the row and column
				sum += matrix[i][matCol] * inputArray[inputRow][i];
			}
			outMatrix[inputRow][matCol] = sum;
		}
	}

	memcpy(matrix, outMatrix, sizeof(float) * 9);
}