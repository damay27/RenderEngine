#pragma once

#include "color.h"
#include "Light.h"
#include "Vector3D.h"
#include "Object.h"
#include "triangle.hpp"
#include <vector>

color ShadowRay(const vector<Object> &objectList, const vector<Light> &lightList, int inputObjectIndex, int inputTriangleIndex, Vector3D point);
color Lambertian(const vector<Object> &objectList, const vector<Light> &lightList, int inputObjectIndex, int inputTriangleIndex, Vector3D point);