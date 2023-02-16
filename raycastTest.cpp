#include <iostream>
#include <raylib.h>
#include "RayCaster.hpp"

int main(void) {
	Texture2D	frameTex;
	Image			frame;

	RayCaster	rayCaster;
	Vector2 cameraPosition = {10, 14};
	Vector2 dirVector = {-1, 0};
	Vector2 planeVector = {0, 0.66};

	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Raycast-raylib-demo");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		frame = rayCaster.renderFrame();
		frameTex = LoadTextureFromImage(frame);
		BeginDrawing();
			DrawTexture(frameTex, 0, 0, WHITE);
		EndDrawing();
	}
}
