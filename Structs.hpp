#ifndef STRUCTS_H
#define STRUCTS_H

#include <raylib.h>

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

#endif // STRUCTS_H
