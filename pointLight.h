#pragma once
#include "Vector3D.h"

class pointLight
{
public:
	pointLight();
	~pointLight();


private:
	float intensity;
	Vector3D position;
};

