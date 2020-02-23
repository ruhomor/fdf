#include "fdf.h"

//TODO figure out setpixel???

int	bitabs(int n)
{
    int	m;

    m = n >> 31;
    return ((m & -n) | (~m & n));
}

void	initvals(t_point *d, t_point *s, t_point *start, t_point *end, int z)
{
	start->x *= z;
	start->y *= z;
	end->x *= z;
	end->y *= z;
	d->x = bitabs(end->x - start->x);
	d->y = bitabs(end->y - start->y);
	s->x = -1;
	s->y = -1;
	if (start->x < end->x)
		s->x = 1;
	if (start->y < end->y)
		s->y = 1;
}

void drawline(t_point start, t_point end, t_window meme) 
{
	t_point d;
	t_point s;
	int	e;
	int	e2;

	initvals(&d, &s, &start, &end, meme->zoom);
	//setPixel(end); //x2y2
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, color);
	while(start.x != end.x || start.y != end.y)
	{
		e2 = e * 2;
		//setPixel(start);
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, color);
		if(e2 > -d.y) 
		{
			e -= d.y;
			start.x += s.x;
		}
		if(e2 < d.x) 
		{
			e += d.x;
			start.y += s.y;
		}
	}
}
