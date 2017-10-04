#pragma once
#include <iostream>

namespace AuxLib {

	inline float RandomBinomial() { return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX)); }
	inline float lerp(float a, float b, float f) { return a + f * (b - a); }
	inline Vector2D rotate(Vector2D vector, float orientation) { 
		Vector2D rotatedVector;
		rotatedVector.x = vector.x * cos(orientation*DEG2RAD) - vector.y * sin(orientation*DEG2RAD);
		rotatedVector.y = vector.x * sin(orientation*DEG2RAD) + vector.y * cos(orientation*DEG2RAD);
		return rotatedVector;
	}

}
