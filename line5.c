#include "fdf.h"

void			supslp2(t_point *cr, t_2dpoint *inter, t_window *meme, int grad)
{
	float		alpha;
	t_point		cur;

	cr->x = fixedtoint(inter->x);
	cur = *cr;
	alpha = (fractionalpart(inter->x));
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
				  rgbtohex(cur.color, 1 - alpha));
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x + 1, cur.y,
				  rgbtohex(cur.color, alpha));
	inter->x += grad;
}

void			sloper2(t_point start, t_point end, t_2dpoint d, t_window *meme)
{
	int			grad;
	t_point		cur;
	t_2dpoint	inter;

	if (end.y < start.y)
		swap(&start, &end);
	if ((start.y <= WINY) && (end.y >= 0) && (ft_min(start.x, end.x) <= WINX)
		&& (ft_max(start.x, end.x) >= 0))
	{
		grad = fractofixed(d.x, d.y);
		inter.x = inttofixed(start.x) + grad;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y,
					  rgbtohex(start.color, 1));
		cur = start;
		cur.y++;
		while (cur.y < end.y)
		{
			supslp2(&cur, &inter, meme, grad);
			cur.y++;
			cur.color = cpy(cur, start, end);
		}
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y,
					  rgbtohex(end.color, 1));
	}
}

void			drawlinecool(t_point start, t_point end, t_window *meme)
{
	t_2dpoint	d;

	initlinecool(&start, &end, &d, meme);
	if (vertical(start, end, d, meme) == 1)
		return ;
	if (horizontal(start, end, d, meme) == 1)
		return ;
	if (abs(d.y) < d.x)
		sloper1(start, end, d, meme);
	else
		sloper2(start, end, d, meme);
}

long int		iai(long int t0, long int t2, float alpha)
{
	return (round(t0 + ((float)(t2 - t0)) * alpha));
}

unsigned char	iac(unsigned char t0, unsigned char t2, float alpha)
{
	return (round(t0 + ((float)(t2 - t0)) * alpha));
}