#pragma once
#include <cmath>
#define UTILS_PI 3.14159f

namespace gloop {

	// Angles
	float radToDeg(float rad);
	float degToRad(float deg);

	float degCos(float angle);
	float degAcos(float angle);
	float degSin(float angle);
	float degTan(float angle);

}