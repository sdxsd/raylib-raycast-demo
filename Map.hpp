#ifndef MAP_H
#define MAP_H

class Map {
	private:
		char	**map_data;
		int		height;
		int		width;
	public:
		Map(int x, int y);
		~Map(void);
		char	**map_generate(void);
		void	print_map(void);
		void	border_walls(void);
};

#endif // MAP_H
