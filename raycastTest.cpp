#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <iostream>

#define WIN_WIDTH 640
#define WIN_HEIGHT 640
#define CLLSIZE 64

// Thank you lodev.org.
#define mapWidth 24
#define mapHeight 24
int map[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	drawVert(Image& destImage, int x, int drawStart, int drawEnd, Color color) {
	ImageDrawLine(&destImage, x, drawStart, x, drawEnd, color);
}

int	main(void) {
	Image	renderResult;
	Vector2	cameraPosition = {10, 14};
	Vector2 dirVector = {-1, 0};
	Vector2 planeVector = {0, 0.66};

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Raycast-raylib-demo");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
			for (int x = 0; x < WIN_WIDTH; x++) {
				float cameraX = 2 * x / double(WIN_WIDTH);
				Vector2 rayDir = {
					dirVector.x + planeVector.x * cameraX,
					dirVector.y + planeVector.y * cameraX
				};
				int mapX = int(cameraPosition.x), mapY = int(cameraPosition.y);
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
					sideDistX = (cameraPosition.x - mapX) * deltaDistY;
				} else {
					stepX = 1;
					sideDistX = (mapX + 1.0 - cameraPosition.x) * deltaDistX;
				} if (rayDir.y < 0) {
					stepY = -1;
					sideDistY = (cameraPosition.y - mapY) * deltaDistY;
				} else {
				}
				while (hit == 0) {
					if (sideDistX < sideDistY) {
						sideDistX += deltaDistX;
						mapX += stepX;
						side = 0;
					}
					else {
						sideDistY += deltaDistY;
						mapY += stepY;
						side = 1;
					}
					if (map[mapX][mapY] > 0) {
						std::cout << "hit" << std::endl;
						hit = 1;
					}
				}
				if (side == 0) perpWallDist = (sideDistX - deltaDistX);
				else          perpWallDist = (sideDistY - deltaDistY);

				int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
				int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
				if(drawEnd >= WIN_HEIGHT)drawEnd = WIN_HEIGHT - 1;
				Color color;
				switch(map[mapX][mapY])
				{
					case 1:  color = RED;  break; //red
					case 2:  color = GREEN;  break; //green
					case 3:  color = BLUE;   break; //blue
					case 4:  color = WHITE;  break; //white
					default: color = YELLOW; break; //yellow
				}

				//give x and y sides different brightness
				if (side == 1) {color.r -= 5, color.b -= 5, color.g -= 5;};

				//draw the pixels of the stripe as a vertical line
				drawVert(x, drawStart, drawEnd, color);
			EndDrawing();
		}
	}
}
