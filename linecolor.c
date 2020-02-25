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
	//d->color.r = bitabs(end->color.r - start->color.r);
	//d->color.g = bitabs(end->color.g - start->color.g);
	//d->color.b = bitabs(end->color.b - start->color.b);
	s->x = -1;
	s->y = -1;
	//s->color.r = -1;
	//s->color.g = -1;
	//s->color.b = -1;
	if (start->x < end->x)
		s->x = 1;
	if (start->y < end->y)
		s->y = 1;
	//if (start->color.r < end->color.r)
	//	s->color.r = 1;
	//if (start->color.g < end->color.g)
	//	s->color.g = 1;
	//if (start->color.b < end->color.b)
	//	s->color.b = 1;
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
	int		e;
	int		e2;

	printf("suka %d\n", map->cell[start.y][start.x]);
	printf("blyat %d\n", map->cell[end.y][end.x]);
	start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x]; //zoom?
	zoomaiso(&start, &end, meme);
	initvals(&d, &s, &start, &end);
	initerr(d, &e, &e2);
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, rgbtohex(end.color));
/*	while (start.x != end.x || start.y != end.y)
	{
		e2 = e * 2;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr,
				start.x, start.y, rgbtohex(start.color));
		if (e2 > -d.y)
		{
			e -= d.y;
			start.x += s.x;
		}
		if (e2 < d.x)
		{
			e += d.x;
			start.y += s.y;
		}
	}
	*/
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, rgbtohex(start.color)); //debug
}
