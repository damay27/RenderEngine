#pragma once
#include "Vector3D.h"
#include "Transform3D.h"
#include "RenderImage.h"
#include "Light.h"
#include <vector>
class Camera
{
public:
	/*
	All needed members are initialized to defualt values through this contructor. They can be modified later through
	member functions. The camer position is specified through the transform matrix translate components.
	*/
	Camera(Transform3D transform, int horizontalRes, int verticalRes);
	~Camera();

	void setResolution(int horizontal, int vertical);
	int getHorizontalResolution();
	int getVerticalResolution();

	void setCameraSettings(float horizontalViewAngle, float verticalViewAngle, float focalLength);
	float getHorizontalViewAngle();
	float getVerticalViewAngle();
	float getFocalLength();

	RenderImage render(const vector<Object> &objectList, const vector<Light> &lightList);

private:
	Transform3D transform;//This sets the position and location of the camera and is used to calculate pixel points
	Vector3D location;//The location specifies the position of the focal point of the camera and acts as the pivot point
	int hRes, vRes;
	float hViewAngle, vViewAngle, focalLength;
	vector<Vector3D> pixelPoints;

	void computePixelPoints();//This function is called internally by the render function
};

