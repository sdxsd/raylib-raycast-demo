#include "RayCaster.hpp"

void	RayCaster::drawVert(VertLine& line) {
	ImageDrawLine(&imageBuffer, line.xCoord, line.startPoint, line.xCoord, line.endPoint, line.color);
}
