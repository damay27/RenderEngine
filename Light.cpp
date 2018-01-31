#include "stdafx.h"
#include "Light.h"


Light::Light(const Vector3D  &position, const color &lightColor, float intensity): position(position), lightColor(lightColor), intensity(intensity)
{
}


Light::~Light()
{
}


void Light::setPosition(const Vector3D &position) {
	this->position = position;
}


Vector3D Light::getPostion()const {
	return position;
}


void Light::setColor(const color &lightColor) {
	this->lightColor = lightColor;
}


color Light::getColor()const {
	return lightColor;
}


void Light::setIntensity(const float &intensity) {//intensity should be < 1
	this->intensity = intensity;
}


float Light::getIntensity()const {
	return intensity;
}