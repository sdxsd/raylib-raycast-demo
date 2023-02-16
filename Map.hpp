#ifndef MAP_H
#define MAP_H

#include "Structs.hpp"

class Map {
	private:
		char		**mapData;
		int			height;
		int			width;
		IntVector2	startPos;
	public:
		Map(int x, int y);
		char	**mapGenerate(void);
		void	printMap(void);
		void	borderWalls(void);
		// Getters.
		char	getCoord(int x, int y) { return (mapData[y][x]); };
		int		getHeight(void) const { return (height); };
		int		getWidth(void) const { return (width); };
		IntVector2	getStart(void) const { return (startPos); };
};

#endif // MAP_H
