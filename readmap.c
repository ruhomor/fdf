#include <stdio.h>
#include "fdf.h"

void	maperror(t_map *map)
{
	int		**cell;

	if (map)
	{
		if (map->cell)
		{
			cell = map->cell;
			ft_putstr_fd("invalid map?", 2);
			while (*cell)
			{
				free(*cell);
				cell++;
			}
			free(map->cell);
		}
		free(map);
	}
}

int	**addline(t_map *map, int *arr)
{
	int	**new;
	int	**buf;
	int	**cell;
	int	lines;

	printf("addline func:\n\n");
	lines = map->height; //what?
	new = (int**)malloc(sizeof(*new) * (map->height + 2)); //alloc c1
	buf = new;
	cell = map->cell;
	while (lines)
	{
		printf("writing line %d\n", lines);
		*buf++ = *cell++;
		lines--;
	}
	*buf++ = arr;
	printf("adding line\n");
	*buf = NULL;
	if (map->cell)
	    free(map->cell); //free old c1
	map->cell = new;
	return (new);
}

int	*reallocints(int **ptr, int msize, int *arr)
{
	int	*newarr;
	int	*rem;
	int	*newptr;

	rem = arr;
	newarr = (int*)malloc(sizeof(*newarr) * msize); //realloc a1
	newptr = newarr;
	while (rem != *ptr)
		*newptr++ = *rem++;
	free(arr); //free old a1
	*ptr = newptr;
	return (newarr);
}

int		ft_ints(char *mapline, t_map *map)
{
	int		msize; //size_t?
	int		mleft; //size_t?
	char	**buf;
	int		*ptr;
	int		*arr;
	char		**tof;

	//map->cells = addline(map);
	msize = BUFF_MSIZE;
	buf = ft_strsplit(mapline, ' '); //alloc b1
	tof = buf;
	arr = (int*)malloc(sizeof(*arr) * msize); //alloc a1
	ptr = arr;
	mleft = msize;
	while (*buf)
	{
		*ptr++ = ft_atoi(*buf++);
		if (!(--mleft))
		{
			arr = reallocints(&ptr, msize + BUFF_MSIZE, arr); //realloc a1
			mleft += BUFF_MSIZE;
			msize += BUFF_MSIZE;
		}
	}
	free(tof); //free b1??? TODO
	map->cell = addline(map, reallocints(&ptr, msize - mleft, arr)); //realloc a1
	return (msize - mleft);
}

void	readmap(t_map *map, char *file)
{
	int	fd;
	char	*mapline;

	fd = open(file, O_RDONLY, 0);
	get_next_line(fd, &mapline);
    map->height = 0;
	map->width = ft_ints(mapline, map);
	map->height++;
	while (get_next_line(fd, &mapline))
	{
		if (ft_ints(mapline, map) == map->width)
			map->height++;
		else
		{
			maperror(map);
			break;
		}
	}
	free(mapline);
	close(fd);
}
