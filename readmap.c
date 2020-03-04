#include "fdf.h"

void		whatever(long int *arr, char **buf, long int **ptr, char ***tof)
{
	*tof = buf;
	*ptr = arr;
}

void		neveragain(int *a, int *b)
{
	*a += BUFF_MSIZE;
	*b += BUFF_MSIZE;
}

int			ft_ints(char *mapline, t_map *map)
{
	t_2dpoint	m;
	char		**buf;
	long int	*ptr;
	long int	*arr;
	char		**tof;

	m = initftints(&buf, &arr, mapline);
	whatever(arr, buf, &ptr, &tof);
	while (*buf)
	{
		if ((*ptr = ft_atoi(*buf)) > map->max)
			map->max = *ptr;
		if (*ptr < map->min)
			map->min = *ptr;
		ptr++;
		free(*buf++);
		if (!(--m.y))
		{
			arr = reallocints(&ptr, m.x + BUFF_MSIZE, arr);
			neveragain(&m.x, &m.y);
		}
	}
	free(tof);
	map->cell = addline(map, reallocints(&ptr, m.x - m.y, arr));
	return (m.x - m.y);
}

void		somef(t_map *map, char **mapline, int fd)
{
	get_next_line(fd, mapline);
	map->height = 0;
	map->max = MAX;
	map->min = MIN;
	map->width = ft_ints(*mapline, map);
	map->height++;
}

void		readmap(t_map *map, char *file, t_window *meme)
{
	int		fd;
	char	*mapline;

	if ((fd = open(file, O_RDONLY, 0)) < 0)
	{
		ft_putstr_fd("failed to open file\n", 2);
		maperror(map, meme);
	}
	somef(map, &mapline, fd);
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
