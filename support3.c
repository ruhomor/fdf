#include "fdf.h"

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
