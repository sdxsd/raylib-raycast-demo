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

Map::Map(int x, int y) {
	width = x;
	height = y;

	mapData = (char**)calloc(sizeof(char*), height);
	if (!mapData)
		throw printf("Malloc failure\n");
	for (int i = 0; i <= height; i++)
		if (!(mapData[i] = (char*)calloc(sizeof(char), width)))
			throw printf("Malloc failure\n");
	for (int i = 0; i <= height; i++)
		for (int z = 0; z <= width; z++)
			mapData[i][z] = '#';
	mapGenerate();
}

Map::~Map(void) {
	for (int i = 0; i < height; i++)
		free(mapData[i]);
	std::cout << "Map freed" << std::endl;
}

int	get_seed(void) {
	int	fd;
	int	*num;
	int	ret;

	num = (int*)malloc(sizeof(int));
	if (!num)
		return (-1);
	fd = open("/dev/urandom", O_RDONLY);
	read(fd, num, sizeof(int));
	ret = *num;
	free(num);
	close(fd);
	return (ret);
}

char **Map::mapGenerate(void) {
	int	g_tunnels = 0;
	int	start_x, start_y, x, y;
	int	length, direction, last_direction;

	last_direction = -1;
	start_x = GetRandomValue(0, width);
	start_y = GetRandomValue(0, height);
	x = start_x;
	y = start_y;
	while (g_tunnels < MAX_TUNNELS - 30) {
		SetRandomSeed(get_seed());
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
					mapData[y--][x] = '.';
			case 1:
				for (int i = 0; y < height && i < length; i++)
					mapData[y++][x] = '.';
			case 2:
				for (int i = 0; x > 0 && i < length; i++)
					mapData[y][x--] = '.';
			case 3:
				for (int i = 0; x < width && i < length; i++)
					mapData[y][x++] = '.';
		}
		if (x == width || y == height) {
			x = start_x;
			y = start_y;
		}
		g_tunnels++;
	}
	return (mapData);
}
