/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:42:45 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 06:42:49 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			initvals(t_point *d, t_point *s, t_point *start, t_point *end)
{
	d->x = labs(end->x - start->x);
	d->y = labs(end->y - start->y);
	s->x = -1;
	s->y = -1;
	if (start->x < end->x)
		s->x = 1;
	if (start->y < end->y)
		s->y = 1;
}

void			initerr(t_point d, int *e, int *e2)
{
	*e = -d.y;
	if (d.x > d.y)
		*e = d.x;
	*e /= 2;
	*e2 = 0;
}

int				rgbtohex(t_color color, double alpha)
{
	int hex;

	hex = (((char)(color.r * alpha) & 0xff) << 16) |
		(((char)(color.g * alpha) & 0xff) << 8) |
		((char)(color.b * alpha) & 0xff);
	return (hex);
}

int				zoomer(t_point *start, t_window *meme)
{
	int		zoom;

	zoom = meme->zoom;
	start->x *= zoom;
	start->y *= zoom;
	start->z *= zoom;
	start->z *= meme->attitude;
	return (zoom);
}

void			zoomaiso(t_point *start, t_window *meme)
{
	int		zoom;
	double	ugol;
	t_color	bcolor;

	ugol = 0.6;
	zoom = zoomer(start, meme);
	if (meme->prjk != 1)
	{
		start->x -= meme->map->width / 2 * zoom;
		start->y -= meme->map->height / 2 * zoom;
	}
	bcolor = start->color;
	*start = transformxyz(*start, meme->angle);
	start->color = bcolor;
	if (meme->prjk != 1)
	{
		start->x += meme->shift.x;
		start->y += meme->shift.y;
	}
	if (meme->prjk == 1)
	{
		start->x += meme->shift.x * cos(ugol) + meme->shift.y * sin(ugol);
		start->x = (start->x - start->y) * cos(ugol);
		start->y = (start->y + start->x) * sin(ugol) - start->z;
	}
}
