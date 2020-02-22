#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	map = (t_map*)malloc(sizeof(*map));
	readmap(map);
	return (0);
}
