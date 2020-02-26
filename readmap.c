#include <stdio.h>
#include "fdf.h"

void	maperror(t_map *map)
{
	long int	**cell;

	if (map)
	{
		if (map->cell)
		{
			cell = map->cell;
			ft_putstr_fd("invalid map?", 2);
			while (*cell)
			{
				printf("beepbeep\n");
				free(*cell);
				cell++;
			}
			free(map->cell);
		}
		free(map);
		map = NULL;
	}
}

long int	**addline(t_map *map, long int *arr)
{
	long int	**new;
	long int	**buf;
	long int	**cell;
	int		lines;

	printf("addline func:\n\n");
	lines = map->height; //what?
	new = (long**)malloc(sizeof(*new) * (map->height + 2)); //alloc c1
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

long int	*reallocints(long int **ptr, int msize, long int *arr)
{
	long int	*newarr;
	long int	*rem;
	long int	*newptr;

	rem = arr;
	newarr = (long int*)malloc(sizeof(*newarr) * msize); //realloc a1
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
	long int	*ptr;
	long int	*arr;
	char		**tof;

	//map->cells = addline(map);
	msize = BUFF_MSIZE;
	buf = ft_strsplit(mapline, ' '); //alloc b[1][1]
	tof = buf;
	arr = (long*)malloc(sizeof(*arr) * msize); //alloc a1
	ptr = arr;
	mleft = msize;
	while (*buf)
	{
		if ((*ptr = ft_atoi(*buf)) > map->max)
			map->max = *ptr;
		if (*ptr < map->min)
			map->min = *ptr;
		ptr++;
		free(*buf++); //free b[1]
		if (!(--mleft))
		{
			arr = reallocints(&ptr, msize + BUFF_MSIZE, arr); //realloc a1
			mleft += BUFF_MSIZE;
			msize += BUFF_MSIZE;
		}
	}
	free(tof); //free b[1][1] TODO
	map->cell = addline(map, reallocints(&ptr, msize - mleft, arr)); //realloc a1
	printf("?%d = %d?\n", msize - mleft, map->width);
	return (msize - mleft);
}
/*
int	max(int *arr, int w)
{
	int	max;
	int	i;

	max = *arr;
	i = -1;
	while (++i < w)
		if (max < *arr)
			max = *(arr - 1);
	return (max);
}

int	min(int *arr, int w)
{
	int	min;
	int	i;

	min = *arr;
	i = -1;
	while (++i < w)
		if (min > *arr++)
			min = *(arr - 1);
	return (min);
}
*/
void	readmap(t_map *map, char *file)
{
	int	fd;
	char	*mapline;

	fd = open(file, O_RDONLY, 0);
	get_next_line(fd, &mapline);
	map->height = 0;
	map->max = MAX;
	map->min = MIN;
	map->width = ft_ints(mapline, map);
	map->height++;
	//map->max = max(*(map->cell), map->width);
	//map->min = min(*(map->cell), map->width);
	free(mapline);
	while (get_next_line(fd, &mapline)) //mapline free???
	{
		if (ft_ints(mapline, map) == map->width)
		{
			map->height++;
			free(mapline);
		}
		else
		{
			maperror(map);
			break ;
		}
	}
	free(mapline);
	close(fd);
}
