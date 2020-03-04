/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:43:06 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 06:43:07 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			initlinecool(t_point *start, t_point *end, t_2dpoint *d,
		t_window *meme)
{
	start->z = meme->map->cell[start->y][start->x];
	end->z = meme->map->cell[end->y][end->x];
	zoomaiso(start, meme);
	zoomaiso(end, meme);
	d->x = (end->x > start->x) ? (end->x - start->x) : (start->x - end->x);
	d->y = (end->x > start->x) ? (end->y - start->y) : (start->y - end->y);
}

int				vertical(t_point start, t_point end, t_2dpoint d,
							t_window *meme)
{
	t_point	cur;

	if ((d.x == 0) && (start.x >= 0) && (start.x <= WINX) &&
		(ft_min(start.y, end.y) <= WINY) && (ft_max(start.y, end.y >= 0)))
	{
		if (end.y < start.y)
			swap(&start, &end);
		cur = start;
		while (cur.y <= end.y)
		{
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
					rgbtohex(cur.color, 1));
			cur.y++;
			cur.color = cpy(cur, end, start);
		}
		return (1);
	}
	return (0);
}

int				horizontal(t_point start, t_point end, t_2dpoint d,
		t_window *meme)
{
	t_point	cur;

	if (d.y == 0 && (start.y >= 0) && (start.y <= WINY) &&
		(ft_min(start.x, end.x) <= WINX) && (ft_max(start.x, end.x) >= 0))
	{
		if (end.x < start.x)
			swap(&start, &end);
		cur = start;
		while (cur.x <= end.x)
		{
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
					rgbtohex(cur.color, 1));
			cur.x++;
			cur.color = cpx(cur, start, end);
		}
		return (1);
	}
	return (0);
}

void			supslp1(t_point *cr, t_2dpoint *inter, t_window *meme, int grad)
{
	float		alpha;
	t_point		cur;

	cr->y = fixedtoint(inter->y);
	cur = *cr;
	alpha = (fractionalpart(inter->y));
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
			rgbtohex(cur.color, 1 - alpha));
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y + 1,
			(rgbtohex(cur.color, alpha)));
	inter->y += grad;
}

void			sloper1(t_point start, t_point end, t_2dpoint d, t_window *meme)
{
	int			grad;
	t_point		cur;
	t_2dpoint	inter;

	if (end.x < start.x)
		swap(&start, &end);
	if ((start.x <= WINX) && (end.x >= 0) && (ft_min(start.y, end.y) <= WINY)
		&& (ft_max(start.y, end.y) >= 0))
	{
		grad = fractofixed(d.y, d.x);
		inter.y = inttofixed(start.y) + grad;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y,
				rgbtohex(start.color, 1));
		cur = start;
		cur.x++;
		while (cur.x < end.x)
		{
			supslp1(&cur, &inter, meme, grad);
			cur.x++;
			cur.color = cpx(cur, start, end);
		}
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y,
				rgbtohex(end.color, 1));
	}
}
