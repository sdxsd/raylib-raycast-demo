#include "RayCaster.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <raylib.h>

static Color getWallColor(char element) {
	Color	color;

	switch (element) {
		case '#':
			color = RED;
			break;
		case 2:
			color = GREEN;
			break;
		case 3:
			color = BLUE;
			break;
		case 4:
			color = WHITE;
			break;
		default:
			color = YELLOW;
			break;
	}
	return (color);
}

static void	setupStepDirection(RayVariables& ray, RayCamera& rayCam) {
	if (ray.rayDir.x < 0) {
		ray.stepDirection.x = -1;
		ray.sideDistances.x = (rayCam.camPos.x - ray.ImapCoords.x) * ray.deltaDistances.x;
	} else {
		ray.stepDirection.x = 1;
		ray.sideDistances.x = (ray.ImapCoords.x + 1.0 - rayCam.camPos.x) * ray.deltaDistances.x;
	}
	if (ray.rayDir.y < 0) {
		ray.stepDirection.y = -1;
		ray.sideDistances.y = (rayCam.camPos.y - ray.ImapCoords.y) * ray.deltaDistances.y;
	} else {
		ray.stepDirection.y = 1;
		ray.sideDistances.y = (ray.ImapCoords.y + 1.0 - rayCam.camPos.y) * ray.deltaDistances.y;
	}
}

static int castUntilHit(RayVariables& ray, Map& map) {
	int	hit = 0;
	int	side;

	while (hit == 0) {
		if (ray.sideDistances.x < ray.sideDistances.y) {
			ray.sideDistances.x += ray.deltaDistances.x;
			ray.ImapCoords.x += ray.stepDirection.x;
			side = 0;
		} else {
			ray.sideDistances.y += ray.deltaDistances.y;
			ray.ImapCoords.y += ray.stepDirection.y;
			side = 1;
		}
		if (map.getCoord(ray.ImapCoords.x, ray.ImapCoords.y) == '#') {
			hit = 1;
		}
	}
	return (side);
}

VertLine genLine(RayVariables& ray, Map& map, int x, int side) {
	VertLine	result;
	double		perpWallDist;
	Color			color;

	if (side == 0)
		perpWallDist = (ray.sideDistances.x - ray.deltaDistances.x);
	else
		perpWallDist = (ray.sideDistances.y - ray.deltaDistances.y);
	int lineHeight = (int)((WIN_HEIGHT / perpWallDist));
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	color = getWallColor(map.getCoord(ray.ImapCoords.x, ray.ImapCoords.y));
	if (side == 1) {
		color.r -= 50, color.b -= 10, color.g -= 10;
	};
	result.xCoord = x;
	result.startPoint = drawStart;
	result.endPoint = drawEnd;
	result.color = color;
	return (result);
}

VertLine RayCaster::castRay(RayCamera &rayCam, int x) {
	VertLine			result;
	RayVariables	ray;
	int						side;

	ray.cameraX = 2 * x / double(WIN_WIDTH) - 1;
	ray.rayDir.x = rayCam.dV.x + rayCam.pV.x * ray.cameraX;
	ray.rayDir.y = rayCam.dV.y + rayCam.pV.y * ray.cameraX;
	ray.ImapCoords = { int(rayCam.camPos.x), int(rayCam.camPos.y) };
	ray.deltaDistances = { abs(1 / ray.rayDir.x), abs(1 / ray.rayDir.y) };
	setupStepDirection(ray, rayCam);
	side = castUntilHit(ray, map);
	return (genLine(ray, map, x, side));
}

void	RayCaster::drawVert(VertLine line) {
	ImageDrawLine(&imageBuffer, line.xCoord, line.startPoint, line.xCoord, line.endPoint, line.color);
}

Image& RayCaster::renderFrame() {
	ImageClearBackground(&imageBuffer, BLACK);
	for (int x = 0; x <= WIN_WIDTH; x++)
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

void RayCaster::handleInput() {
	float deltaTime = GetFrameTime();
	float moveSpeed = 5.0 * deltaTime;
	float rotSpeed = 3.0 * deltaTime;

	if (IsKeyDown(KEY_UP)) {
		if (map.getCoord((int)(rayCam.camPos.x + rayCam.dV.x * moveSpeed), int(rayCam.camPos.y)) != '#')
			rayCam.camPos.x += rayCam.dV.x * moveSpeed;
		if (map.getCoord(int(rayCam.camPos.x), (int)(rayCam.camPos.y + rayCam.dV.y * moveSpeed)) != '#')
			rayCam.camPos.y += rayCam.dV.y * moveSpeed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		if (map.getCoord((int)(rayCam.camPos.x - rayCam.dV.x * moveSpeed), int(rayCam.camPos.y)) != '#')
			rayCam.camPos.x -= rayCam.dV.x * moveSpeed;
		if (map.getCoord(int(rayCam.camPos.x), (int)(rayCam.camPos.y - rayCam.dV.y * moveSpeed)) != '#')
			rayCam.camPos.y -= rayCam.dV.y * moveSpeed;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		double oldDirX = rayCam.dV.x;
		rayCam.dV.x = rayCam.dV.x * cos(-rotSpeed) - rayCam.dV.y * sin(-rotSpeed);
		rayCam.dV.y = oldDirX * sin(-rotSpeed) + rayCam.dV.y * cos(-rotSpeed);
		double oldPlaneX = rayCam.pV.x;
		rayCam.pV.x = rayCam.pV.x * cos(-rotSpeed) - rayCam.pV.y * sin(-rotSpeed);
		rayCam.pV.y = oldPlaneX * sin(-rotSpeed) + rayCam.pV.y * cos(-rotSpeed);
	}
	if (IsKeyDown(KEY_LEFT)) {
		double oldDirX = rayCam.dV.x;
		rayCam.dV.x = rayCam.dV.x * cos(rotSpeed) - rayCam.dV.y * sin(rotSpeed);
		rayCam.dV.y = oldDirX * sin(rotSpeed) + rayCam.dV.y * cos(rotSpeed);
		double oldPlaneX = rayCam.pV.x;
		rayCam.pV.x = rayCam.pV.x * cos(rotSpeed) - rayCam.pV.y * sin(rotSpeed);
		rayCam.pV.y = oldPlaneX * sin(rotSpeed) + rayCam.pV.y * cos(rotSpeed);
	}
}
