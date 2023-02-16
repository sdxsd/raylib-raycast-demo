#include "RayCamera.hpp"

RayCamera::RayCamera(void) {
	dV = {-1, 0};
	pV = {0, 0.66};
	camPos.x = 0;
	camPos.y = 0;
}

RayCamera::RayCamera(const IntVector2& startPos) {
	dV = {-1, 0};
	pV = {0, 0.66};
	camPos.x = (float)startPos.x;
	camPos.y = (float)startPos.y;
}

RayCamera& RayCamera::operator=(const IntVector2& camPosVec) {
	this->camPos.x = (float)camPosVec.x;
	this->camPos.y = (float)camPosVec.y;
	return (*this);
}
