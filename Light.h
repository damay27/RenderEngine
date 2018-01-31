#pragma once
#include "Vector3D.h"
#include "color.h"

class Light
{
public:
	Light(const Vector3D  &position, const color &lightColor, float intensity);
	~Light();
	void setPosition(const Vector3D &position);
	Vector3D getPostion()const;
	void setColor(const color &lightColor);
	color getColor()const;
	void setIntensity(const float &intensity);
	float getIntensity()const;

private:
	Vector3D position;
	color lightColor;
	float intensity;
};

