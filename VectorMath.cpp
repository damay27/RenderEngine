#include "stdafx.h"
#include"VectorMath.h"

vector<float> crossProduct(vector<float> a, vector<float> b) {
	float term1 = a.at(1)*b.at(2) - b.at(1)*a.at(2);
	float term2 = -(a.at(0)*b.at(2) - b.at(0)*a.at(2));
	float term3 = a.at(0)*b.at(1) - b.at(0)*a.at(1);
	return vector<float>({ term1, term2, term3 });
}

float dotProduct(vector<float> a, vector<float> b) {
	return a.at(0)*b.at(0) + a.at(1)*b.at(1) + a.at(2) + b.at(2);
}