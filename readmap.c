#include "fdf.h"

void	maperror(t_map *map)
{
	int		**cells;
	int		width;

	cells = map->cells;
	ft_putstr_fd("invalid map?");
	while (cells)
	{
		free(*cells);
		cells++;
	}
}

int		ft_ints(char *mapline, t_map *map)
{
	int		msize;
	int		mleft;
	char	**buf;
	int		*ptr;
	int		*arr;

	msize = BUF_MSIZE;
	curw = 0;
	buf = ft_strsplit(mapline, ' '); //TODO width?? write //-no matter
	arr = (int*)malloc(msize * sizeof(*arr));
	ptr = arr;
	mleft = msize;
	while ((buf) && (*buf))
	{
		*ptr++ = ft_atoi(*buf++);
		if (!(--mleft))
		{

		}
	//realloc for cells
		
	}
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
			maperror(map);
	}
	fd = open(file, O_RDONLY, 0);
}
