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

void		initerr(t_point d, int *e, int *e2)
{
	*e = -d.y;
	if (d.x > d.y)
		*e = d.x;
	*e /= 2;
	*e2 = 0;
}

int		color(t_point meme)
{
	return (meme.r * 16 * 16 + meme.g * 16 + meme.b);
}

void		drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
	t_point	d;
	t_point	s;
	int		e;
	int		e2;

	initvals(&d, &s, &start, &end);
	initerr(d, &e, &e2);
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, color(end));
	while (start.x != end.x || start.y != end.y)
	{
		e2 = e * 2;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr,
				start.x, start.y, color(start));
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
}
