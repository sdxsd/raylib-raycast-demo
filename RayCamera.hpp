#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>
#include "Structs.hpp"

class RayCamera {
	public:
		Vector2	camPos;
		Vector2 dV;
		Vector2 pV;
		RayCamera(void);
		RayCamera(const IntVector2& startPos);
		RayCamera& operator=(const IntVector2& camPosVec);
};

#endif // CAMERA_H
