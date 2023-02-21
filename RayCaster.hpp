#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "RayCamera.hpp"
#include "Map.hpp"

#define D_MAPSIZE_X 24
#define D_MAPSIZE_Y 24

#define WIN_WIDTH 1152
#define WIN_HEIGHT 1152

#include "Structs.hpp"

class RayCaster {
	private:
		Image		imageBuffer;
		RayCamera	rayCam;
		Map		map;
		VertLine	castRay(RayCamera& rayCam, int x);
		void		drawVert(VertLine line);
	public:
		RayCaster(void);
		RayCaster(int x, int y);
		~RayCaster(void);
		Image&	renderFrame(void);
		void	handleInput(void);
};

#endif // RAYCASTER_H
