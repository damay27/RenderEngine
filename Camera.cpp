#include "stdafx.h"
#include "Camera.h"
#include "Raycast.h"
#include "Shade.h"
#include <cmath>

#define PI 3.14159265f
#define deg2rad PI/180.0f

Camera::Camera(Transform3D transformInput, int horizontalRes, int verticalRes) :
	transform(transformInput), hRes(horizontalRes), vRes(verticalRes), hViewAngle(60), vViewAngle(45), focalLength(1)
{
	location = transform.applyTransform(Vector3D(0,0,0), Vector3D(0, 0, 0));//move the camera position to the correct location in global space

	pixelPoints.reserve(hRes*vRes);//reserve a large enough size to hold all the pixels

}


Camera::~Camera()
{
}


void Camera::setResolution(int horizontal, int vertical) {
	hRes = horizontal;
	vRes = vertical;
	pixelPoints.reserve(hRes*vRes);
}


int Camera::getHorizontalResolution() {
	return hRes;
}


int Camera::getVerticalResolution() {
	return vRes;
}


void Camera::setCameraSettings(float horizontalViewAngle, float verticalViewAngle, float FocalLength) {
	hViewAngle = horizontalViewAngle;
	vViewAngle = verticalViewAngle;
	focalLength = FocalLength;
}


float Camera::getHorizontalViewAngle() {
	return hViewAngle;
}


float Camera::getVerticalViewAngle() {
	return vViewAngle;
}


float Camera::getFocalLength() {
	return focalLength;
}


RenderImage Camera::render(const vector<Object> &objectList, const vector<Light> &lightList) {

	computePixelPoints();//compute the grid points for each pixel

	RenderImage img(hRes, vRes);

	int pixelPointsIndex = 0;

	for (int y = 0; y < vRes; y++) {//loog through each column of the image
		for (int x = 0; x < hRes; x++) {//loop through each row of the image

			/*
			This data is updated each time a ray hits a triangle and is used to 
			find the closest triangle for each pixel. Some of this data is also passed to the shading
			functions. 
			*/
			float minContactDistance = float( pow(10, 10) );
			int closestObjectIndex = -1;
			int closestTriangleIndex = -1;
			Vector3D closestContact;

			for (int objectIndex = 0; objectIndex < objectList.size(); objectIndex++) {//loop through each object in the scene

				int numberTriangles = objectList[objectIndex].numberOfTriangles();
				for (int triangleIndex = 0; triangleIndex < numberTriangles; triangleIndex++) {//loop through each triangle in the image

					Vector3D contact = Raycast(location, pixelPoints.at(pixelPointsIndex) - location, objectList.at(objectIndex).getTriangle(triangleIndex));//do ray cast

					if (contact.isNull()==false && location.distance(contact) < minContactDistance) {//check if the ray hit anything and if it is the closest hit found so far
						
						//if the contact is the closest to the camera update the data 
						minContactDistance = location.distance(contact);
						closestObjectIndex = objectIndex;
						closestTriangleIndex = triangleIndex;
						closestContact = contact;
					}

				}
			}

			if (closestObjectIndex==-1) {//if the ray never hit any objects pixel to black
				img.setPixel(x, y, 0, 0, 0);
			}
			else // If it did hit something shade the pixel useing one of the shading functions
			{

				Material objectMat = objectList[closestObjectIndex].getMaterial();
				color c;

				if (objectMat.getShadingMethod() == LAMBERTIAN) {
					c = Lambertian(objectList, lightList, closestObjectIndex, closestTriangleIndex, closestContact);
				}
				else {
					c = ShadowRay(objectList, lightList, closestObjectIndex, closestTriangleIndex, closestContact);
				}

				img.setPixel(x, y, c.getRed8bit(), c.getGreen8bit(), c.getBlue8bit());

			}
			pixelPointsIndex++;
		}
	}

	return img;
}

/*
Pixel points are the points in 3d space that coraspond to each pixel in the image. The ray is shot from the camera
location through each pixel point to deternine ray direction. Each point is first calculated at one focal length distance down the x axis 
with the horizontal displacemnt being along the y axis and vertical displacment being along the z axis. Each point is then transformed according to the camera transform. 
*/
void Camera::computePixelPoints() {

	//Find the location of the upper left corner
	float hStart = tan(-(hViewAngle*deg2rad) / 2) * focalLength;
	float vStart = tan( (vViewAngle*deg2rad) / 2) * focalLength;
	
	//Calculate the horizontal and vertical spacing between each pixel
	float hStep = abs(2 * hStart) / hRes;
	float vStep = abs(2 * vStart) / vRes;

	float verticalPosition = vStart;
	float horizontalPostion = hStart;


	for (int z = 0; z < vRes; z++) {
		verticalPosition -= vStep;//scan vertically from top to bottom
		for (int y = 0; y < hRes; y++) {
			horizontalPostion += hStep;//scan horizontally from left to right

			Vector3D point = transform.applyTransform(Vector3D(0,0,0), Vector3D(focalLength, horizontalPostion, verticalPosition) );//apply the transform

			pixelPoints.push_back(point);
			
		}
		horizontalPostion = hStart;//reset the horizontal position at the end of each row
	}

}