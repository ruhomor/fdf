#include "fdf.h"
#include <stdio.h> //useless
#include <math.h>

int		bitabs(int n)
{
	int		m;

	m = n >> 31;
	return ((m & -n) | (~m & n));
}

void		initvals(t_point *d, t_point *s, t_point *start, t_point *end)
{
	d->x = bitabs(end->x - start->x);
	d->y = bitabs(end->y - start->y);
	d->color.r = end->color.r - start->color.r;
	d->color.g = end->color.g - start->color.g;
	d->color.b = end->color.b - start->color.b;
	s->x = -1;
	s->y = -1;
	s->color.r = -1;
	s->color.g = -1;
	s->color.b = -1;
	if (start->x < end->x)
		s->x = 1;
	if (start->y < end->y)
		s->y = 1;
/*	if (start->color.r < end->color.r)
		s->color.r = 1;
	if (start->color.g < end->color.g)
		s->color.g = 1;
	if (start->color.b < end->color.b)
		s->color.b = 1;
		*/
}

void		initerr(t_point d, int *e, int *e2)
{
	*e = -d.y;
	if (d.x > d.y)
		*e = d.x;
	*e /= 2;
	*e2 = 0;
}

int		rgbtohex(t_color color)
{
	int	hex;

	//color.r = 255;
	//color.g = 255;
	//color.b = 255;
	hex = ((color.r & 0xff) << 16) | ((color.g & 0xff) << 8) | (color.b & 0xff);
	return (hex);
}

void		zoomaiso(t_point *start, t_point *end, t_window *meme)
{
	int	zoom;
	double	ugol;
	double	angle;

	ugol = 0.8;
	angle = meme->angle;
	zoom = meme->zoom;
	start->x *= zoom;
	start->y *= zoom;
	start->z *= zoom; //z -?
	end->x *= zoom;
	end->y *= zoom;
	end->z *= zoom; //z -?
	start->x = (start->x - start->y) * cos(ugol);
	start->y = (start->y + start->x) * sin(ugol) - start->z;
	end->x = (end->x - end->y) * cos(ugol);
	end->y = (end->y + end->x) * sin(ugol) - end->z;
	start->x += 600;
	start->y += 300;
	end->x += 600;
	end->y += 300;
}

t_color		cp(t_point cur, t_point start, t_point end)
{
	t_color	color;

	color.r = start.color.r + (end.color.r - start.color.r) * (cur.x - start.x) / (end.x - start.x);
	color.g = start.color.g + (end.color.g - start.color.g) * (cur.x - start.x) / (end.x - start.x);
	color.b = start.color.b + (end.color.b - start.color.b) * (cur.x - start.x) / (end.x - start.x);
	return (color);
}

void		drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
	t_point	d;
	t_point	s;
	t_point	cur;
	int		e;
	int		e2;

	printf("suka %ld\n", map->cell[start.y][start.x]);
	printf("blyat %ld\n", map->cell[end.y][end.x]);
	start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x]; //zoom?
	zoomaiso(&start, &end, meme);
	initvals(&d, &s, &start, &end);
	initerr(d, &e, &e2);
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, rgbtohex(end.color));
	cur = start;
	while (cur.x != end.x || cur.y != end.y)
	{

		e2 = e * 2;
		//start.color = pp(map, start.x, start.y, meme->zoom);
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr,
				cur.x, cur.y, rgbtohex(cur.color));
		cur.color = cp(cur, start, end);
		if (e2 > -d.y)
		{
			e -= d.y;
			cur.x += s.x;
		}
		if (e2 < d.x)
		{
			e += d.x;
			cur.y += s.y;
		}
	}
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, rgbtohex(start.color)); //debug
}
