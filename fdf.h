/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:56:37 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 07:18:04 by kachiote         ###   ########.fr       */
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

typedef struct			s_shift
{
	long int			x;
	long int			y;
	long int			u_flag;
	long int			d_flag;
	long int			l_flag;
	long int			r_flag;
}						t_shift;

typedef struct			s_angle
{
	double				a;
	double				b;
}						t_angle;

typedef struct			s_2dpoint
{
	int					x;
	int					y;
}						t_2dpoint;

typedef struct			s_2dline
{
	t_2dpoint			e;
	t_2dpoint			d;
}						t_2dline;

typedef struct			s_color
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}						t_color;

typedef struct			s_fcolor
{
	float				r;
	float				g;
	float				b;
}						t_fcolor;

typedef struct			s_point
{
	long int			x;
	long int			y;
	long int			z;
	t_color				color;
}						t_point;

typedef struct			s_line
{
	t_point				a;
	t_point				b;
}						t_line;

typedef struct			s_fpoint
{
	float				x;
	float				y;
	float				z;
	t_fcolor			color;
}						t_fpoint;

typedef	struct			s_map
{
	long int			**cell;
	int					width;
	int					height;
	long int			max;
	long int			min;
	unsigned long int	colorrange;
}						t_map;

typedef struct			s_ass
{
	float				phi;
	int					j;
}						t_ass;

typedef	struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					zoom;
	t_angle				angle;
	int					drag_flag;
	t_map				*map;
	long int			*zbuf;
	t_shift				shift;
	int					attitude;
	int					renmod;
	int					prjk;
}						t_window;

void					maperror(t_map *map, t_window *meme);
t_point					transformxyz(t_point point, t_angle angle);
t_point					transformx(t_point point, double angle);
t_point					transformy(t_point point, double angle);
long int				**addline(t_map *map, long int *arr);
long int				*reallocints(long int **ptr, int msize, long int *arr);
int						ft_ints(char *mapline, t_map *map);
void					readmap(t_map *map, char *file, t_window *meme);
int						bitabs(int n);
void					initvals(t_point *d, t_point *s, t_point *start,
		t_point *end);
void					drawline(t_point start, t_point end, t_window *meme);
void					drawlineoldbutgold(t_point start, t_point end,
		t_window *meme,
		t_map *map);
void					drawlinecool(t_point start, t_point end,
		t_window *meme);
void					drawmap(t_window *meme);
t_color					pp(t_map *map, int x, int y, int zoom);
void					blackout(t_window *meme);
void					trianglebuf(t_point t0, t_point t1, t_point t2,
		t_window *meme);
void					trianglebufre(t_point t0, t_point t1, t_point t2,
		t_window *meme, t_map *map);
t_2dpoint				initftints(char ***buf, long int **arr, char *mapline);
int						rgbtohex(t_color color, double alpha);
void					zoomaiso(t_point *start, t_window *meme);
void					swapxy(long int *a, long int *b);
void					swap(t_point *a, t_point *b);
t_color					cpx(t_point cur, t_point start, t_point end);
t_color					cpy(t_point cur, t_point start, t_point end);
long int				iai(long int t0, long int t2, float alpha);
unsigned char			iac(unsigned char t0, unsigned char t2, float alpha);
long int				ft_min(long int a, long int b);
long int				ft_max(long int a, long int b);
long int				inttofixed(int value);
long int				fixedtoint(int value);
int						fractofixed(int a, int b);
float					fractionalpart(int a);
void					initlinecool(t_point *start, t_point *end, t_2dpoint *d,
		t_window *meme);
int						vertical(t_point start, t_point end, t_2dpoint d,
		t_window *meme);
int						horizontal(t_point start, t_point end, t_2dpoint d,
		t_window *meme);
void					sloper1(t_point start, t_point end,
		t_2dpoint d, t_window *meme);
void					liner(t_window *meme, int renmode, int i, int j);
void					triangle(t_window *meme, int renmode, int i, int j);
void					liner1(t_window *meme, int renmode, int i, int j);
void					liner2(t_window *meme, int renmode, int i, int j);
void					wotrewot(t_color *wot, t_color hsv,
		unsigned char remainder);
void					initbuf(long int *arr, long int size);
t_color					regionhandle(t_color wot, t_color hsv,
		unsigned char region);
void					shufflr(t_color *rgb, unsigned char a,
		unsigned char b, unsigned char c);
t_color					hsvtorgb(t_color hsv);
void					escape_butt(t_window *meme);
int						mouse_move(int x, int y, void *p);
int						mouse_press(int button, int x, int y, void *p);
int						mouse_release(int button, int x, int y, void *p);
int						key_press1(int keycode, void *p);
t_window				*initwindow(void);
void					memerememe(t_map *map, t_window *meme);

#endif
