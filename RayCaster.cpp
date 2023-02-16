#include "RayCaster.hpp"
#include <iostream>

VertLine RayCaster::castRay(RayCamera &rayCam, int x) {
  VertLine result;
  float cameraX = 2 * x / double(WIN_WIDTH);
  Vector2 rayDir = {rayCam.dV.x + rayCam.pV.x * cameraX,
					rayCam.dV.y + rayCam.pV.y * cameraX};
  int mapX = int(rayCam.camPos.x), mapY = int(rayCam.camPos.y);
  double sideDistX;
  double sideDistY;
  double deltaDistX = (rayDir.x == 0) ? 1e30 : std::abs(1 / rayDir.x);
  double deltaDistY = (rayDir.y == 0) ? 1e30 : std::abs(1 / rayDir.y);
  double perpWallDist;
  int stepX;
  int stepY;
  int hit = 0;
  int side;

  if (rayDir.x < 0) {
	stepX = -1;
	sideDistX = (rayCam.camPos.x - mapX) * deltaDistY;
  } else {
	stepX = 1;
	sideDistX = (mapX + 1.0 - rayCam.camPos.x) * deltaDistX;
  }
  if (rayDir.y < 0) {
	stepY = -1;
	sideDistY = (rayCam.camPos.y - mapY) * deltaDistY;
  } else {
	  stepY = 1;
	  sideDistY = (mapY + 1.0 - rayCam.camPos.y) * deltaDistY;
  }
  while (hit == 0) {
	if (sideDistX < sideDistY) {
	  sideDistX += deltaDistX;
	  mapX += stepX;
	  side = 0;
	} else {
	  sideDistY += deltaDistY;
	  mapY += stepY;
	  side = 1;
	  std::cout << "mapy" << mapY << std::endl;
	}
	if (map.getCoord(mapX, mapY) == '#') {
	  std::cout << "hit" << std::endl;
	  hit = 1;
	}
  }
  if (side == 0)
	perpWallDist = (sideDistX - deltaDistX);
  else
	perpWallDist = (sideDistY - deltaDistY);

  std::cout << rayCam.camPos.x << std::endl;
  std::cout << rayCam.camPos.y << std::endl;
  std::cout << "perpWallDist" << perpWallDist << std::endl;
  int lineHeight = (int)((WIN_HEIGHT / perpWallDist));
  std::cout << "lineHeight: " << lineHeight << std::endl;
  int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
  if (drawStart < 0)
	drawStart = 0;
  int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
  if (drawEnd >= WIN_HEIGHT)
	drawEnd = WIN_HEIGHT - 1;
  Color color;
  switch (map.getCoord(mapX, mapY)) {
  case '#':
	color = RED;
	break; // red
  case 2:
	color = GREEN;
	break; // green
  case 3:
	color = BLUE;
	break; // blue
  case 4:
	color = WHITE;
	break; // white
  default:
	color = YELLOW;
	break; // yellow
  }

  // give x and y sides different brightness
  if (side == 1) {
	color.r -= 5, color.b -= 5, color.g -= 5;
  };
  result.xCoord = x;
  std::cout << "x:" << x << std::endl;
  result.startPoint = drawStart;
  std::cout << "drawStart: " << drawStart << std::endl;
  result.endPoint = drawEnd;
  std::cout << "drawEnd: " << drawEnd << std::endl;
  std::cout << x << std::endl;
  result.color = color;
  return (result);
}

void	RayCaster::drawVert(VertLine line) {
	ImageDrawLine(&imageBuffer, line.xCoord, line.startPoint, line.xCoord, line.endPoint, line.color);
}

Image& RayCaster::renderFrame() {
	for (int x = 0; x < WIN_WIDTH; x++)
		drawVert(castRay(rayCam, x));
	return (imageBuffer);
}

RayCaster::RayCaster(void):
	map(D_MAPSIZE_X, D_MAPSIZE_Y) {
	rayCam = map.getStart();
	imageBuffer = GenImageColor(WIN_WIDTH, WIN_HEIGHT, WHITE);
	map.printMap();
	std::cout << "RayCaster sucessfully constructed.";
}

RayCaster::~RayCaster(void) {
	;
}
