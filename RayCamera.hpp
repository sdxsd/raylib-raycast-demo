#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

class RayCamera {
	public:
		Vector2	camPos;
		Vector2 dV;
		Vector2 pV;
		RayCamera(int x, int y);
};

#endif // CAMERA_H
