#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "RayCamera.hpp"
#include "Map.hpp"

#define D_MAPSIZE_X 24
#define D_MAPSIZE_Y 24

typedef struct s_IntVector2 {
	int	x;
	int	y;
} IntVector2;

typedef struct s_vertLine {
	Color	color;
	int	xCoord;
	int	startPoint;
	int	endPoint;
}	VertLine;

class RayCaster {
	private:
		Image		imageBuffer;
		RayCamera	rayCam;
		Map			map;
		VertLine&	castRay(int x);
		void		drawVert(VertLine& line);
	public:
		RayCaster(void);
		RayCaster(int x, int y);
		~RayCaster(void);
		Image&	renderFrame(void);
};

#endif // RAYCASTER_H
