/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:56:25 by kachiote          #+#    #+#             */
/*   Updated: 2020/02/23 22:56:27 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void				escape_map_butt(t_map *map)
{
	long int	**cell;

	if (map)
	{
		if (map->cell)
		{
			cell = map->cell;
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

void				escape_butt(t_window *meme)
{
	t_map		*map;
	long int	*zbuf;

	if (meme)
	{
		map = meme->map;
		escape_map_butt(map);
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
	exit(0);
}

void				shufflr(t_color *rgb, unsigned char a, unsigned char b,
		unsigned char c)
{
	rgb->r = a;
	rgb->g = b;
	rgb->b = c;
}

void				wotrewot(t_color *wot, t_color hsv, unsigned char remainder)
{
	wot->r = (hsv.b * (255 - hsv.g)) >> 8;
	wot->g = (hsv.b * (255 - ((hsv.g * remainder) >> 8))) >> 8;
	wot->b = (hsv.b * (255 - ((hsv.g * (255 - remainder)) >> 8))) >> 8;
}

t_color				regionhandle(t_color wot, t_color hsv, unsigned char region)
{
	t_color rgb;

	rgb = (t_color){0, 0, 0};
	if (region == 0)
		shufflr(&rgb, hsv.b, wot.b, wot.r);
	else if (region == 1)
		shufflr(&rgb, wot.g, hsv.b, wot.r);
	else if (region == 2)
		shufflr(&rgb, wot.r, hsv.b, wot.b);
	else if (region == 3)
		shufflr(&rgb, wot.r, wot.g, hsv.b);
	else if (region == 4)
		shufflr(&rgb, wot.b, wot.r, hsv.b);
	else
		shufflr(&rgb, hsv.b, wot.r, wot.g);
	return (rgb);
}

t_color				hsvtorgb(t_color hsv)
{
	t_color			rgb;
	unsigned char	region;
	unsigned char	remainder;
	t_color			wot;

	rgb = (t_color){0, 0, 0};
	if (hsv.g == 0)
	{
		shufflr(&rgb, hsv.b, hsv.b, hsv.b);
		return (rgb);
	}
	region = hsv.r / 43;
	remainder = (hsv.r - (region * 43)) * 6;
	wotrewot(&wot, hsv, remainder);
	return (regionhandle(wot, hsv, region));
}

void				sm(t_color rgb, t_color *hsv, unsigned char rgbmin,
		unsigned char rgbmax)
{
	if (rgbmax == rgb.r)
		hsv->r = 0 + 43 * (rgb.g - rgb.b) / (rgbmax - rgbmin);
	else if (rgbmax == rgb.g)
		hsv->r = 85 + 43 * (rgb.b - rgb.r) / (rgbmax - rgbmin);
	else
		hsv->r = 171 + 43 * (rgb.r - rgb.g) / (rgbmax - rgbmin);
}

unsigned char		rgbminft(t_color rgb)
{
	if (rgb.r < rgb.g)
	{
		if (rgb.r < rgb.b)
			return (rgb.r);
		else
			return (rgb.b);
	}
	else
	{
		if (rgb.g < rgb.b)
			return (rgb.g);
		else
			return (rgb.b);
	}
}

unsigned char		rgbmaxft(t_color rgb)
{
	if (rgb.r > rgb.g)
	{
		if (rgb.r > rgb.b)
			return (rgb.r);
		else
			return (rgb.b);
	}
	else
	{
		if (rgb.g > rgb.b)
			return (rgb.g);
		else
			return (rgb.b);
	}
}

t_color				rgbtohsv(t_color rgb)
{
	t_color			hsv;
	unsigned char	rgbmin;
	unsigned char	rgbmax;

	rgbmin = rgbminft(rgb);
	rgbmax = rgbmaxft(rgb);
	hsv.b = rgbmax;
	if (hsv.b == 0)
	{
		hsv.r = 0;
		hsv.g = 0;
		return (hsv);
	}
	hsv.g = 255 * (int)(rgbmax - rgbmin) / hsv.b;
	if (hsv.g == 0)
	{
		hsv.r = 0;
		return (hsv);
	}
	sm(rgb, &hsv, rgbmin, rgbmax);
	return (hsv);
}

t_color				pp(t_map *map, int x, int y, int zoom)
{
	t_color color;

	zoom--;
	zoom++;
	if (map->colorrange != 0)
		color.r = (130 - 0) * map->cell[y][x] / map->colorrange;
	else
		color.r = (130 - 0) * map->cell[y][x];
	color.g = 255;
	color.b = 255;
	return (hsvtorgb(color));
}

t_point				ft_xy(int x, int y)
{
	static t_point point0;
	static t_point point;

	point = point0;
	point0.x = x;
	point0.y = y;
	return (point);
}

int					mouse_move(int x, int y, void *p)
{
	t_window	*meme;
	t_point		point;
	double		da;
	double		db;

	meme = (t_window*)p;
	point = ft_xy(x, y);
	db = (point.x != 0) ? (double)(x - point.x) / point.x : 0;
	da = (point.y != 0) ? (double)(y - point.y) / point.y : 0;
	if (meme->drag_flag == 1)
	{
		meme->angle.a += da;
		meme->angle.b += db;
		mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
		drawmap(meme);
	}
	return (0);
}

int					mouse_press(int button, int x, int y, void *p)
{
	t_window *meme;

	meme = (t_window *)p;
	if (button == 1)
	{
		meme->drag_flag = 1;
		ft_xy(x, y);
	}
	if (button == 4)
	{
		meme->zoom += 1;
		mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
		drawmap(meme);
	}
	if (button == 5)
	{
		meme->zoom -= 1;
		mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
		drawmap(meme);
	}
	return (0);
}

int					mouse_release(int button, int x, int y, void *p)
{
	t_window *meme;

	x++;
	x--;
	y++;
	y--;
	meme = (t_window *)p;
	if (button == 1)
		meme->drag_flag = 0;
	return (0);
}

t_point				transformx(t_point point, double angle)
{
	t_point tmp;

	tmp.x = point.x;
	tmp.y = point.y * cos(angle) + point.z * sin(angle);
	tmp.z = -point.y * sin(angle) + point.z * cos(angle);
	return (tmp);
}

t_point				transformy(t_point point, double angle)
{
	t_point tmp;

	tmp.x = point.x * cos(angle) + point.z * sin(angle);
	tmp.y = point.y;
	tmp.z = -point.x * sin(angle) + point.z * cos(angle);
	return (tmp);
}

t_point				transformxyz(t_point point, t_angle angle)
{
	return (transformy(transformx(point, angle.a), angle.b));
}

void				kph(int keycode, t_window *meme)
{
	if (keycode == 126)
		meme->shift.u_flag = (meme->shift.u_flag == 1) ? 0 : -1;
	if (keycode == 125)
		meme->shift.d_flag = (meme->shift.d_flag == -1) ? 0 : 1;
	if (keycode == 124)
		meme->shift.r_flag = (meme->shift.r_flag == -1) ? 0 : 1;
	if (keycode == 123)
		meme->shift.l_flag = (meme->shift.l_flag == 1) ? 0 : -1;
	if (keycode == 69)
		meme->attitude += 1;
	if (keycode == 78)
		meme->attitude -= 1;
	if (keycode == 53)
		escape_butt(meme);
	if (keycode == 18)
		meme->renmod = 1;
	if (keycode == 19)
		meme->renmod = 2;
	if (keycode == 20)
		meme->renmod = 3;
	if (keycode == 21)
		meme->renmod = 4;
}

int					key_press1(int keycode, void *p)
{
	t_window *meme;

	meme = (t_window *)p;
	kph(keycode, meme);
	if (keycode == 35)
	{
		meme->prjk += 1;
		meme->prjk %= 2;
	}
	meme->shift.x +=
			meme->shift.r_flag + meme->shift.l_flag;
	meme->shift.y += meme->shift.u_flag + meme->shift.d_flag;
	mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
	drawmap(meme);
	return (0);
}

int					key_release1(int keycode, void *p)
{
	t_window *meme;

	meme = (t_window *)p;
	if (keycode == 126)
		meme->shift.u_flag = (meme->shift.u_flag == -1) ? 0 : 1;
	if (keycode == 125)
		meme->shift.d_flag = (meme->shift.d_flag == 1) ? 0 : -1;
	if (keycode == 124)
		meme->shift.r_flag = (meme->shift.r_flag == 1) ? 0 : -1;
	if (keycode == 123)
		meme->shift.l_flag = (meme->shift.l_flag == -1) ? 0 : 1;
	return (0);
}

void				initbuf(long int *arr, long int size)
{
	long int i;

	i = -1;
	while (++i < size)
		*arr++ = MAX;
}

t_window			*initwindow(void)
{
	t_window *meme;

	meme = (t_window *)malloc(sizeof(*meme));
	meme->zbuf = (long int *)malloc(
			WINY * WINX * sizeof(*(meme->zbuf)));
	initbuf(meme->zbuf, WINX * WINY);
	meme->win_ptr = NULL;
	meme->drag_flag = 0;
	meme->shift.r_flag = 0;
	meme->shift.l_flag = 0;
	meme->shift.u_flag = 0;
	meme->shift.d_flag = 0;
	meme->angle.a = 0;
	meme->angle.b = 0;
	meme->zoom = 2;
	meme->attitude = 1;
	meme->renmod = 1;
	meme->prjk = 0;
	return (meme);
}

void				hookhandler(t_window *meme)
{
	mlx_hook(meme->win_ptr, 6, 0, mouse_move, meme);
	mlx_hook(meme->win_ptr, 4, 0, mouse_press, meme);
	mlx_hook(meme->win_ptr, 5, 0, mouse_release, meme);
	mlx_hook(meme->win_ptr, 2, 0, key_press1, meme);
	mlx_hook(meme->win_ptr, 3, 0, key_release1, meme);
	mlx_loop(meme->mlx_ptr);
}

void				memerememe(t_map *map, t_window *meme)
{
	meme->shift.x = WINX / 2 - map->width / 2;
	meme->shift.y = WINY / 2 - map->height / 2;
	meme->mlx_ptr = mlx_init();
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, WINX, WINY, "MEME");
	map->colorrange = map->max - map->min;
	meme->map = map;
	drawmap(meme);
	hookhandler(meme);
}

int					main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;

	meme = initwindow();
	if (argc != 2)
	{
		ft_putstr_fd("fdf: wrond number of arguments\n", 2);
		maperror(NULL, meme);
	}
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	readmap(map, argv[1], meme);
	memerememe(map, meme);
	return (0);
}

void				liner(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
						j, 1)}, meme, map);
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i,
						j + 1, 1)}, meme, map);
	if (renmode == 2)
		drawlinecool(
				(t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
						j, 1)}, meme, map);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)},
				meme, map);
}

void				liner1(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j,
						1)}, meme, map);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
						j, 1)}, meme, map);
}

void				liner2(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1,
						1)}, meme, map);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i,
						j + 1, 1)}, meme, map);
}

void				triangle(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode >= 3)
		trianglebuf(
				(t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i,
						j + 1, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
						j, 1)}, meme, map);
	if (renmode >= 4)
		trianglebuf((t_point){.x = i + 1, .y = j + 1, .color = pp(map,
				i + 1, j + 1, 1)},
					(t_point){.x = i, .y = j + 1, .color = pp(map, i,
							j + 1, 1)},
					(t_point){.x = i + 1, .y = j, .color = pp(map,
							i + 1, j, 1)}, meme, map);
}

void				linertriangle(t_window *meme, int renmode, int i, int j)
{
	liner(meme, renmode, i, j);
	triangle(meme, renmode, i, j);
}

void				drawmap(t_window *meme)
{
	int		i;
	int		j;
	int		renmode;
	t_map	*map;

	map = meme->map;
	renmode = meme->renmod;
	j = -1;
	while (++j < map->height - 1)
	{
		i = -1;
		while (++i < map->width - 1)
			linertriangle(meme, renmode, i, j);
	}
	j = map->height - 1;
	i = -1;
	while (++i < map->width - 1)
		liner1(meme, renmode, i, j);
	i = map->width - 1;
	j = -1;
	while (++j < map->height - 1)
		liner2(meme, renmode, i, j);
	initbuf(meme->zbuf, WINX * WINY);
}
