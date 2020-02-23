#include <stdio.h>
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	int	i;
	int	j;

	i = 0;
	j = 0;
	argc--;
	map = (t_map*)malloc(sizeof(*map));
	readmap(map, argv[1]);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			printf("%d ", map->cell[i][j++]);
		printf("\n");
		i++;
	}
	maperror(map);
	return (0);
}
