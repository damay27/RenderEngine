#pragma once

#include "color.h"



enum SHADE_TYPE { SHADOW_RAY, LAMBERTIAN };

class Material
{
public:
	Material(SHADE_TYPE shadingMethod, const color &materialColor, int lambertianPower=1);
	Material(const Material &copyMaterial);
	Material();
	~Material();

	SHADE_TYPE getShadingMethod()const;
	void setShadeingMethod(SHADE_TYPE newShadingMethod);

	color getColor()const;
	void setColor(const color &newColor);

	int getlambertianPower()const;
	void setlambertianPower(int lambertianPower);

private: 
	SHADE_TYPE shadingMethod;
	color materialColor;
	int lambertianPower;//This is only used when lambertian shading is selected
};

