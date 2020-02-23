#ifndef FDF_H

# define FDF_H

# include "lib/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
//# include <mlx.h>

# define BUFF_MSIZE 4

typedef	struct	s_map
{
	int	**cell;
	int	width;
	int	height;
}		t_map;

void	maperror(t_map *map);
int	**addline(t_map *map, int *arr);
int	*reallocints(int **ptr, int msize, int *arr);
int		ft_ints(char *mapline, t_map *map);
void	readmap(t_map *map, char *file);

#endif
