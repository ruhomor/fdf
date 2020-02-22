#include "fdf.h"

void	maperror(t_map *map)
{
	int		**cell;

	cell = map->cell;
	ft_putstr_fd("invalid map?", 2);
	while (cell)
	{
		free(*cell);
		cell++;
	}
	free(map->cell);
	free(map);
}

int	**addline(t_map *map, int *arr)
{
	int	**new;
	int	**buf;
	int	**cell;
	int	lines;

	lines = map->height;
	new = (int**)malloc(sizeof(*new) * (map->height + 1));
	buf = new;
	cell = map->cell;
	while (lines)
	{
		*buf++ = *cell++;
		lines--;
	}
	*buf = arr;
	free(map->cell);
	map->cell = new;
	return (new);
}

int	*reallocints(int *ptr, int msize, int *arr)
{
	int	*newarr;
	int	*rem;

	rem = arr;
	newarr = (int*)malloc(sizeof(*newarr) * msize);
	while (arr != ptr)
		*newarr++ = *arr++;
	free(rem);
	return (newarr);
}

int		ft_ints(char *mapline, t_map *map)
{
	int		msize; //size_t?
	int		mleft; //size_t?
	char	**buf;
	int		*ptr;
	int		*arr;

	//map->cells = addline(map);
	msize = BUFF_MSIZE;
	buf = ft_strsplit(mapline, ' '); //TODO width?? write //-no matter
	arr = (int*)malloc(sizeof(*arr) * msize);
	ptr = arr;
	mleft = msize;
	while (*buf)
	{
		*ptr++ = ft_atoi(*buf++);
		if (!(--mleft))
		{
			arr = reallocints(ptr, msize + BUFF_MSIZE, arr);
			mleft += BUFF_MSIZE;
			msize += BUFF_MSIZE;
		}
	}
	map->cell = addline(map, reallocints(ptr, msize - mleft, arr));
	return (msize - mleft);
}

void	readmap(t_map *map, char *file)
{
	int	fd;
	char	*mapline;

	fd = open(file, O_RDONLY, 0);
	get_next_line(fd, &mapline);
	map->width = ft_ints(mapline, map);
	map->height = 1;
	while (get_next_line(fd, &mapline))
	{
		if (ft_ints(mapline, map) == map->width)
			map->height++;
		else
			maperror(map);
	}
}
