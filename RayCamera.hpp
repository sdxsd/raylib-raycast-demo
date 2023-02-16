#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>
#include "Structs.hpp"

class RayCamera {
	public:
		Vector2	camPos;
		Vector2 dV;
		Vector2 pV;
		RayCamera(IntVector2 startPos);
};

#endif // CAMERA_H
