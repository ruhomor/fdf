#include "fdf.h"

void		mappp(t_map *map)
{
	long int	**cell;

	if (map)
	{
		if (map->cell)
		{
			cell = map->cell;
			ft_putstr_fd("invalid map\n", 2);
			while (*cell)
			{
				free(*cell);
				cell++;
			}
			free(map->cell);
		}
		free(map);
		map = NULL;
	}
}

void		maperror(t_map *map, t_window *meme)
{
	long int	*zbuf;

	if (meme)
	{
		zbuf = meme->zbuf;
		if (zbuf)
		{
			free(zbuf);
			zbuf = NULL;
		}
		if (meme->win_ptr != NULL)
			mlx_destroy_window(meme->mlx_ptr, meme->win_ptr);
		free(meme);
		meme = NULL;
	}
	mappp(map);
	exit(0);
}

long int	**addline(t_map *map, long int *arr)
{
	long int	**new;
	long int	**buf;
	long int	**cell;
	int			lines;

	lines = map->height;
	new = (long **)malloc(sizeof(*new) * (map->height + 2));
	buf = new;
	cell = map->cell;
	while (lines)
	{
		*buf++ = *cell++;
		lines--;
	}
	*buf++ = arr;
	*buf = NULL;
	if (map->cell)
		free(map->cell);
	map->cell = new;
	return (new);
}

long int	*reallocints(long int **ptr, int msize, long int *arr)
{
	long int *newarr;
	long int *rem;
	long int *newptr;

	rem = arr;
	newarr = (long int *)malloc(sizeof(*newarr) * msize);
	newptr = newarr;
	while (rem != *ptr)
		*newptr++ = *rem++;
	free(arr);
	*ptr = newptr;
	return (newarr);
}

t_2dpoint	initftints(char ***buf, long int **arr, char *mapline)
{
	t_2dpoint	m;

	m.x = BUFF_MSIZE;
	*buf = ft_strsplit(mapline, ' ');
	*arr = (long *)malloc(sizeof(*arr) * m.x);
	m.y = m.x;
	return (m);
}