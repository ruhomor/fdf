#include "fdf.h"

void	maperror()
{
	ft_putstr_fd("invalid map?");
}

int	ft_ints(char *mapline, t_map *map)
{
	
}

void	readmap(t_map *map, char *file)
{
	int	fd;
	char	*mapline;

	get_next_line(fd, &mapline);
	map->width = ft_ints(mapline, map);
	map->height = 1;
	while (get_next_line(fd, &mapline))
	{
		if (ft_ints(mapline) == map->width)
			map->height++;
		else
			maperror();
	}
	fd = open(file, O_RDONLY, 0);
}
