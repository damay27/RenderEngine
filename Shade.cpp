#include "stdafx.h"
#include "Shade.h"
#include "Raycast.h"


/*
This function deternines if the given point is in shadow and from that determines its color. 
*/
color ShadowRay(const vector<Object> &objectList, const vector<Light> &lightList, int inputObjectIndex, int inputTriangleIndex, Vector3D point) {
	int numberLights = int( lightList.size() );
	int numberObjects = int( objectList.size() );

	vector<color> colors;
	colors.reserve(numberLights);//the number of colors to be averages is always the same as the number of lights

	//get the color of the object that the point is on
	color objectColor = objectList[inputObjectIndex].getMaterial().getColor();


	for (int lightIndex = 0; lightIndex < numberLights; lightIndex++) {//for every light in the scene

		float distance2light = point.distance(lightList[lightIndex].getPostion());

		Vector3D point2light = lightList[lightIndex].getPostion() - point;//this is the direction for the raycast

		bool shadow = false;

		for (int objectIndex = 0; objectIndex < numberObjects; objectIndex++) {//test every object

			Object currentObject = objectList[objectIndex];

			int numberTriangles = currentObject.numberOfTriangles();

			for (int triangleIndex = 0; triangleIndex < numberTriangles; triangleIndex++) {//test if any triangles from the current object are blocking the light ray

				
				Vector3D contact = Raycast(point, point2light, currentObject.getTriangle(triangleIndex));
				

				//detect if the ray hit it's own triangle
				if (inputObjectIndex == objectIndex) {
					if (inputTriangleIndex == triangleIndex) {
						continue;
					}
				}

				if (contact.isNull()) {//if the ray hit nothing then ignor it
					continue;
				}

				else {//if the object is in shadow return the shadow color

					//make sure the object is comes between the point and the light
					float distance = point.distance(contact);

					if (distance < distance2light) {// if the object is in shadow break out of the object and triangle loops
						shadow = true;
						goto computeColor;

					}
				}

			}

		}

computeColor:
		if (shadow) {
			colors.push_back(color(0, 0, 0));//if the object is in shadow for this light the add the color black to the list
		}
		else {
			colors.push_back(objectColor);//if the object is not in shadow add the objects color to the list
		}
	}


	//Sum and average all the colors
	int redSum = 0, greenSum = 0, blueSum = 0;
	for (int colorIndex = 0; colorIndex < numberLights; colorIndex++) {
		color currentColor = colors.at(colorIndex);
		redSum += currentColor.getRed();
		greenSum += currentColor.getGreen();
		blueSum += currentColor.getBlue();
	}

	//return the average color. The number of colors always equals the number of lights
	return color(redSum / numberLights, greenSum / numberLights, blueSum / numberLights);



}


color LambertianSecondStage(const vector<Object> &objectList, Light light, int inputObjectIndex, int inputTriangleIndex, Vector3D point, Material mat) {
	
	float distance2light = point.distance(light.getPostion());
	int numberObjects = int(objectList.size());

	Vector3D point2light = light.getPostion() - point;

	for (int objectIndex = 0; objectIndex < numberObjects; objectIndex++) {//test every object

		Object currentObject = objectList[objectIndex];

		int numberTriangles = currentObject.numberOfTriangles();

		for (int triangleIndex = 0; triangleIndex < numberTriangles; triangleIndex++) {//test if any triangles are blocking the light ray


			Vector3D contact = Raycast(point, point2light, currentObject.getTriangle(triangleIndex));

			if (inputObjectIndex == objectIndex) {
				if (isOnTriangle(currentObject.getTriangle(inputTriangleIndex), contact)) {//detect if the ray hit it's own triangle
					continue;
				}
			}

			if (!contact.isNull()){//if the ray hits a triangle

				float distance = point.distance(contact);//and the contact is in front of the light

				if (distance < distance2light) {
					return (mat.getColor().average(color(0,0,0), .9f));

				}
			}

		}

	}

	//if the point has made it this far its not in shadow
	//do Lambertian calculation

	Vector3D normal = objectList[inputObjectIndex].getTriangle(inputTriangleIndex).getNormal();
	normal = normal.normalize();//The normal must be a unit vector

	point2light = light.getPostion() - point;
	point2light = point2light.normalize();

	float scaler = abs(Dot(normal, point2light) * light.getIntensity());

	scaler = pow(scaler, mat.getlambertianPower());

	color lightColor = light.getColor();

	return lightColor * scaler;



}


color Lambertian(const vector<Object> &objectList, const vector<Light> &lightList, int inputObjectIndex, int inputTriangleIndex, Vector3D point) {
	
	int numberLights = int(lightList.size());

	vector<color> colors;
	colors.reserve(numberLights);

	Material mat = objectList[inputObjectIndex].getMaterial();


	for (int lightIndex = 0; lightIndex < numberLights; lightIndex++) {//for every light in the scene

		colors.push_back( LambertianSecondStage(objectList, lightList[lightIndex], inputObjectIndex, inputTriangleIndex, point, mat) );
		
	}
	int rSum=0, gSum=0, bSum=0;

	int numberColors = int(colors.size());

	for (int colorIndex = 0; colorIndex < numberColors; colorIndex++) {//sum al the colors so they can be averaged
		rSum += colors[colorIndex].getRed();
		gSum += colors[colorIndex].getGreen();
		bSum += colors[colorIndex].getBlue();
	}


	//average the colors
	color returnColor(rSum / numberColors, gSum / numberColors, bSum / numberColors);

	return returnColor.average(mat.getColor());

}