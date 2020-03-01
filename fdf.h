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
# define MIN 2147483647 //TODO
# define MAX -2147483648

# define BUFF_MSIZE 4
# define WINX 2000
# define WINY 1000

typedef struct  s_shift
{
    long int        x;
    long int        y;
    long int        u_flag;
    long int        d_flag;
    long int        l_flag;
    long int        r_flag;
}               t_shift;

typedef struct	s_angle
{
	double			a;
	double			b;
}				t_angle;

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

typedef struct  s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			zoom;
	t_angle			angle;
	int			drag_flag;
	t_map			*map;
	long int        *zbuf;
	t_shift         shift;
	int             attitude;
}				t_window;

void			maperror(t_map *map);
t_point			transformXYZ(t_point point, t_angle angle);
t_point			transformX(t_point point, double angle);
t_point			transformY(t_point point, double angle);
long int			**addline(t_map *map, long int *arr);
long int			*reallocints(long int **ptr, int msize, long int *arr);
int				ft_ints(char *mapline, t_map *map);
void			readmap(t_map *map, char *file);
int				bitabs(int n);
void			initvals(t_point *d, t_point *s, t_point *start, t_point *end);
void			drawline(t_point start, t_point end, t_window *meme, t_map *map);
void			drawmap(t_window *meme, t_map *map);
t_color			pp(t_map *map, int x, int y, int zoom);
void			blackout(t_window *meme);
void            triangle1(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map);
void            triangle2(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map);
void            trianglebuf(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map);

#endif
