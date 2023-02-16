#include <iostream>
#include "RayCaster.hpp"

int	main(void) {
	Vector2	cameraPosition = {10, 14};
	Vector2 dirVector = {-1, 0};
	Vector2 planeVector = {0, 0.66};

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Raycast-raylib-demo");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
			for (int x = 0; x < WIN_WIDTH; x++) {
				drawVert(x, drawStart, drawEnd, color);
			EndDrawing();
		}
	}
}
