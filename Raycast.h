#pragma once
#include  "Triangle.hpp"
#include "Vector3D.h"

bool isOnTriangle(Triangle triangle, Vector3D point);

Vector3D Raycast(Vector3D originPoint, Vector3D direction, Triangle triangle);

