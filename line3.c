#include "fdf.h"

t_color			cpy(t_point cur, t_point start, t_point end)
{
	t_color color;

	if (end.y != start.y)
	{
		color.r = start.color.r +
				  (end.color.r - start.color.r) * (cur.y - start.y) /
				  (end.y - start.y);
		color.g = start.color.g +
				  (end.color.g - start.color.g) * (cur.y - start.y) /
				  (end.y - start.y);
		color.b = start.color.b +
				  (end.color.b - start.color.b) * (cur.y - start.y) /
				  (end.y - start.y);
	}
	else
	{
		color.r = start.color.r;
		color.g = start.color.g;
		color.b = start.color.b;
	}
	return (color);
}

void			swap(t_point *a, t_point *b)
{
	t_point t;

	t = *a;
	*a = *b;
	*b = t;
}

void			swapxy(long int *a, long int *b)
{
	long int c;

	c = *a;
	*a = *b;
	*b = c;
}

long int		ft_min(long int a, long int b)
{
	if (a > b)
		return (b);
	return (a);
}

long int		ft_max(long int a, long int b)
{
	if (a > b)
		return (a);
	return (b);
}