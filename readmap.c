#include <stdio.h>
#include "fdf.h"

void	maperror(t_map *map, t_window *meme)
{
	long int	**cell;
	long int    *zbuf;

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
		map = NULL;
	}
	exit(0);
}

long int	**addline(t_map *map, long int *arr)
{
	long int	**new;
	long int	**buf;
	long int	**cell;
	int		lines;

	lines = map->height;
	new = (long**)malloc(sizeof(*new) * (map->height + 2));
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
	long int	*newarr;
	long int	*rem;
	long int	*newptr;

	rem = arr;
	newarr = (long int*)malloc(sizeof(*newarr) * msize);
	newptr = newarr;
	while (rem != *ptr)
		*newptr++ = *rem++;
	free(arr);
	*ptr = newptr;
	return (newarr);
}

int		ft_ints(char *mapline, t_map *map)
{
	int		msize;
	int		mleft;
	char	**buf;
	long int	*ptr;
	long int	*arr;
	char		**tof;

	msize = BUFF_MSIZE;
	buf = ft_strsplit(mapline, ' ');
	tof = buf;
	arr = (long*)malloc(sizeof(*arr) * msize);
	ptr = arr;
	mleft = msize;
	while (*buf)
	{
		if ((*ptr = ft_atoi(*buf)) > map->max)
			map->max = *ptr;
		if (*ptr < map->min)
			map->min = *ptr;
		ptr++;
		free(*buf++);
		if (!(--mleft))
		{
			arr = reallocints(&ptr, msize + BUFF_MSIZE, arr);
			mleft += BUFF_MSIZE;
			msize += BUFF_MSIZE;
		}
	}
	free(tof);
	map->cell = addline(map, reallocints(&ptr, msize - mleft, arr));
	return (msize - mleft);
}

void	readmap(t_map *map, char *file, t_window *meme)
{
	int	fd;
	char	*mapline;

	if ((fd = open(file, O_RDONLY, 0)) < 0)
	{
		ft_putstr_fd("failed to open file\n", 2);
		maperror(map, meme);
	}
	get_next_line(fd, &mapline);
	map->height = 0;
	map->max = MAX;
	map->min = MIN;
	map->width = ft_ints(mapline, map);
	map->height++;
	free(mapline);
	while (get_next_line(fd, &mapline))
	{
		if (ft_ints(mapline, map) == map->width)
		{
			map->height++;
			free(mapline);
		}
		else
		{
			maperror(map, meme);
			break ;
		}
	}
	free(mapline);
	close(fd);
}
