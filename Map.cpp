#include "Map.hpp"
#include <cstdlib>
#include <raylib.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <time.h>
#include <stdio.h>

Map::Map(const int x, const int y) {
	width = x;
	height = y;

	mapData = new char*[y + 1];
	for (int i = 0; i < y + 1; i++)
		mapData[i] = new char[x + 1];
	for (int i = 0; i < height; i++)
		for (int z = 0; z < width; z++)
			mapData[i][z] = '.';
	mapGenerate();
}

Map::~Map(void) {
	for (int i = 0; i < height; i++)
		free(mapData[i]);
	std::cout << "Map freed" << std::endl;
}

char **Map::mapGenerate(void) {
	int	g_tunnels = 0;
	int	start_x, start_y, x, y;
	int	length, direction, last_direction;

	last_direction = -1;
	SetRandomSeed(time(NULL));
	start_x = GetRandomValue(0, width);
	start_y = GetRandomValue(0, height);
	x = start_x;
	y = start_y;
	startPos.x = start_x;
	startPos.y = start_y;
	while (g_tunnels < MAX_TUNNELS - 30) {
		SetRandomSeed(time(NULL));
		length = GetRandomValue(4, TUNNEL_LENGTH);
		direction = GetRandomValue(0,3);
		if (last_direction == 0 || last_direction == 1)
				direction = GetRandomValue(2,3);
		else if (last_direction == 2 || last_direction == 3)
				direction = GetRandomValue(0,1);
		last_direction = direction;
		switch (direction) {
			case 0:
				for (int i = 0; y > 0 && i < length; i++)
					mapData[y--][x] = '#';
			case 1:
				for (int i = 0; y < height && i < length; i++)
					mapData[y++][x] = '#';
			case 2:
				for (int i = 0; x > 0 && i < length; i++)
					mapData[y][x--] = '#';
			case 3:
				for (int i = 0; x < width && i < length; i++)
					mapData[y][x++] = '#';
		}
		if (x == width || y == height) {
			x = start_x;
			y = start_y;
		}
		g_tunnels++;
	}
	borderWalls();
	mapData[startPos.y][startPos.y] = '.';
	return (mapData);
}

void Map::borderWalls(void) {
	int	iterator_y = 0;
	int	iterator_x = 0;

	while (iterator_y++ < height)
	{
		mapData[iterator_y][width] = '#';
		mapData[iterator_y][0] = '#';
	}
	while (iterator_x++ < width) {
		mapData[height - 1][iterator_x] = '#';
		mapData[0][iterator_x] = '#';
	}
}

void Map::printMap(void) {
	for (int i = 0; i < height; i++) {
		for (int z = 0; z < width; z++) {
			if (i == startPos.y && z == startPos.x)
				std::cout << "p";
			else
				std::cout << mapData[i][z];
		}
		std::cout << std::endl;
	}
}
