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

// cameraX:			Camera angle.
// rayDir:			Direction of the ray.
// IMapCoords:		Integer coordinates of ray.
// sideDistances:	x & y distance to nearest side.
// deltaDistances:	Length from one x or y side to following x or y side.
// stepDirection:	The direction to "step" in as the algorithm continues.
typedef struct s_RayVariables {
	float		cameraX;
	Vector2		rayDir;
	IntVector2	ImapCoords;
	Vector2		sideDistances;
	Vector2		deltaDistances;
	IntVector2	stepDirection;
} RayVariables;

#endif // STRUCTS_H
