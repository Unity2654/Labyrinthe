#include "Utils.h"
#include <iostream>

float gloop::radToDeg(float rad){
	return rad * 180 / UTILS_PI;
}

float gloop::degToRad(float deg){
	return deg * UTILS_PI / 180;
}

float gloop::degCos(float angle){
	return radToDeg(cos(degToRad(angle)));
}

float gloop::degAcos(float angle) {
	return radToDeg(acos(degToRad(angle)));
}

float gloop::degSin(float angle){
	return radToDeg(sin(degToRad(angle)));
}

float gloop::degTan(float angle){
	return radToDeg(tan(degToRad(angle)));
}