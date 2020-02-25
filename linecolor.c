/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:56:48 by kachiote          #+#    #+#             */
/*   Updated: 2020/02/23 22:56:50 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	d->r = bitabs(end->r - start->r);
	d->g = bitabs(end->g - start->g);
	d->b = bitabs(end->b - start->b);
	s->x = -1;
	s->y = -1;
	s->r = -1;
	s->g = -1;
	s->b = -1;
	if (start->x < end->x)
		s->x = 1;
	if (start->y < end->y)
		s->y = 1;
	if (start->r < end->r)
		s->r = 1;
	if (start->g < end->g)
		s->g = 1;
	if (start->b < end->b)
		s->b = 1;
}

void		initerr(t_point d, t_point *e)
{
	e->x = -d.y;
	if (d.x > d.y)
		e->x = d.x;
	e->x /= 2;
	e->y = 0;
}

int		rgbtohex(t_point meme)
{
	int	hex;

	meme.r = 255; //useless
	meme.g = 0; //useless
	meme.b = 0; //useless
	hex = ((meme.r & 0xff) << 16) | ((meme.g & 0xff) << 8) | (meme.b & 0xff);
	return (hex);
}

void		zoomaiso(t_point *start, t_point *end, t_window *meme)
{
	int	zoom;

	zoom = meme->zoom;
	start->x *= zoom;
	start->y *= zoom;
	end->x *= zoom;
	end->y *= zoom; //z -?
	start->x = start->x - start->y * cos(0.8);
	start->y = start->y + start->x * sin(0.8) - start->z;
	end->x = end->x - end->y * cos(0.8);
	end->y = end->y + end->x * sin(0.8) - end->z;
	start->x += 200;
	start->y += 200;
	end->x += 200;
	end->y += 200;
}

void		drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
	t_point	d;
	t_point	s;
	t_point	e; //e.x
	//int	e2; e.y

	printf("suka %d\n", map->cell[start.y][start.x]);
	printf("blyat %d\n", map->cell[end.y][end.x]);
	start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x]; //zoom?
	zoomaiso(&start, &end, meme);
	initvals(&d, &s, &start, &end);
	initerr(d, &e);
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, rgbtohex(end));
	while (start.x != end.x || start.y != end.y)
	{
		e.y = e.x * 2;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr,
				start.x, start.y, rgbtohex(start));
		if (e.y > -d.y)
		{
			e.x -= d.y;
			start.x += s.x;
		}
		if (e.y < d.x)
		{
			e.x += d.x;
			start.y += s.y;
		}
	}
}
