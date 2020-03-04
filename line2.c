/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:42:53 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 06:42:55 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long int		inttofixed(int value)
{
	return (value << 16);
}

long int		fixedtoint(int value)
{
	if (value < 0)
		return ((value >> 16) - 1);
	else
		return (value >> 16);
}

int				fractofixed(int a, int b)
{
	return ((a << 16) / b);
}

float			fractionalpart(int a)
{
	int		p;
	int		s;
	float	d;

	p = a - inttofixed(fixedtoint(a));
	s = 1 << 16;
	d = p;
	return (d / s);
}

t_color			cpx(t_point cur, t_point start, t_point end)
{
	t_color color;

	if (end.x != start.x)
	{
		color.r = start.color.r +
			(end.color.r - start.color.r) * (cur.x - start.x) /
			(end.x - start.x);
		color.g = start.color.g +
			(end.color.g - start.color.g) * (cur.x - start.x) /
			(end.x - start.x);
		color.b = start.color.b +
			(end.color.b - start.color.b) * (cur.x - start.x) /
			(end.x - start.x);
	}
	else
	{
		color.r = start.color.r;
		color.g = start.color.g;
		color.b = start.color.b;
	}
	return (color);
}
