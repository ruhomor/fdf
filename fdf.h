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
# include <math.h>
# include "minilibx_macos/mlx.h"
# define MIN 2147483647
# define MAX -2147483648

# define BUFF_MSIZE 4
# define WINX 2000
# define WINY 1000

typedef struct	s_angle
{
	double			a;
	double			b;
	double			g;
}				t_angle;

typedef struct  s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			zoom;
	t_angle			angle;
	int			drag_flag;
}				t_window;

typedef struct	s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}				t_color;

typedef struct	s_point
{
	long int		x;
	long int		y;
	long int		z;
	t_color			color;
}				t_point;

typedef	struct	s_map
{
	long int		**cell;
	int			width;
	int			height;
	long int		max;
	long int		min;
	unsigned long int	colorrange;
}				t_map;

void			maperror(t_map *map);
long int			**addline(t_map *map, long int *arr);
long int			*reallocints(long int **ptr, int msize, long int *arr);
int				ft_ints(char *mapline, t_map *map);
void			readmap(t_map *map, char *file);
int				bitabs(int n);
void			initvals(t_point *d, t_point *s, t_point *start, t_point *end);
void			drawline(t_point start, t_point end, t_window *meme, t_map *map);
void			drawmap(t_window *meme, t_map *map);
t_color			pp(t_map *map, int x, int y, int zoom);

#endif
