/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:56:37 by kachiote          #+#    #+#             */
/*   Updated: 2020/02/23 22:56:39 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "lib/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"

# define BUFF_MSIZE 4

typedef struct  s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			zoom;
}				t_window;

typedef struct	s_point
{
	int			x;
	int			y;
	int			r;
	int			g;
	int			b;
}				t_point;

typedef	struct	s_map
{
	int			**cell;
	int			width;
	int			height;
}				t_map;

void			maperror(t_map *map);
int				**addline(t_map *map, int *arr);
int				*reallocints(int **ptr, int msize, int *arr);
int				ft_ints(char *mapline, t_map *map);
void			readmap(t_map *map, char *file);
int				bitabs(int n);
void			initvals(t_point *d, t_point *s, t_point *start, t_point *end);
void			drawline(t_point start, t_point end, t_window *meme, t_map *map);
void			drawmap(t_window *meme, t_map *map);

#endif
