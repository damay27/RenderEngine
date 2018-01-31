#include "stdafx.h"
#include "Material.h"

Material::Material(SHADE_TYPE shadingMethod, const color &materialColor, int lambertianPower): shadingMethod(shadingMethod), materialColor(materialColor), lambertianPower(lambertianPower)
{

}


Material::Material(const Material &copyMaterial) {
	this->materialColor = copyMaterial.getColor();
	this->lambertianPower = copyMaterial.getlambertianPower();
	this->shadingMethod = copyMaterial.getShadingMethod();
}

Material::Material() : shadingMethod(SHADOW_RAY), materialColor(255, 0, 255), lambertianPower(1)
{

}

Material::~Material()
{
}


SHADE_TYPE Material::getShadingMethod()const {
	return shadingMethod;
}


void Material::setShadeingMethod(SHADE_TYPE newShadingMethod) {
	this->shadingMethod = shadingMethod;
}


color Material::getColor()const {
	return materialColor;
}


void Material::setColor(const color &newColor) {
	this->materialColor = newColor;
}


int Material::getlambertianPower()const {
	return lambertianPower;
}


void Material::setlambertianPower(int lambertianPower) {
	this->lambertianPower = lambertianPower;
}