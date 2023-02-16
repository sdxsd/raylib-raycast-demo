#include <iostream>
#include <raylib.h>
#include "RayCaster.hpp"

int main(void) {
	Texture2D	frameTex;
	Image			frame;

	RayCaster	rayCaster;
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "Raycast-raylib-demo");
	SetTargetFPS(60);

		frame = rayCaster.renderFrame();
		frameTex = LoadTextureFromImage(frame);
		BeginDrawing();
			DrawTexture(frameTex, 0, 0, WHITE);
		EndDrawing();
		UnloadTexture(frameTex);
		while (!WindowShouldClose()) {
			;
		}
}
