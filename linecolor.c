#include "fdf.h"
#include <stdio.h> //useless
#include <math.h>

void		initvals(t_point *d, t_point *s, t_point *start, t_point *end)
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

void		initerr(t_point d, int *e, int *e2)
{
	*e = -d.y;
	if (d.x > d.y)
		*e = d.x;
	*e /= 2;
	*e2 = 0;
}

int		rgbtohex(t_color color, double alpha)
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
	t_color	bcolor;

	ugol = 0.0;

	zoom = meme->zoom; //ZOOM Section
	start->x *= zoom;
	start->y *= zoom;
	start->z *= zoom; //z -?
	end->x *= zoom;
	end->y *= zoom;
	end->z *= zoom; //z -?

	bcolor = start->color; //starting point rotation
	*start = transformXYZ(*start, meme->angle); //TODO zero exception??? crush
	start->color = bcolor;

	bcolor = end->color; //ending point rotation
	*end = transformXYZ(*end, meme->angle); //bred bug
	end->color = bcolor;

    start->x = (start->x - start->y) * cos(ugol); //Z-axis section
    start->y = (start->y + start->x) * sin(ugol) - start->z;
    end->x = (end->x - end->y) * cos(ugol);
    end->y = (end->y + end->x) * sin(ugol) - end->z;

	start->x += 600; //xy shift
	start->y += 300;
	end->x += 600;
	end->y += 300;
}

t_color		cp(t_point cur, t_point start, t_point end)
{
	t_color	color;

	if (end.x != start.x) {
        color.r = start.color.r + (end.color.r - start.color.r) * (cur.x - start.x) / (end.x - start.x);
        color.g = start.color.g + (end.color.g - start.color.g) * (cur.x - start.x) / (end.x - start.x);
        color.b = start.color.b + (end.color.b - start.color.b) * (cur.x - start.x) / (end.x - start.x);
    } else {
        color.r = start.color.r;
        color.g = start.color.g;
        color.b = start.color.b;
	}
	return (color);
}
/*
void		drawline(t_point start, t_point end, t_window *meme, t_map *map) //start and end r wot?
{
	t_point	d;
	t_point	s;
	t_point	cur;
	int		e;
	int		e2;

	//printf("suka %ld\n", map->cell[start.y][start.x]);
	//printf("blyat %ld\n", map->cell[end.y][end.x]);
	start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x]; //zoom?
	zoomaiso(&start, &end, meme);
	initvals(&d, &s, &start, &end);
	initerr(d, &e, &e2);
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x,
			end.y, rgbtohex(end.color));
	cur = start;
	while (cur.x != end.x || cur.y != end.y)
	{
        printf("%ld %ld %ld %ld %ld %ld\n", cur.x, end.x, cur.y, end.y, s.x, s.y);


		e2 = e * 2;
		//start.color = pp(map, start.x, start.y, meme->zoom);
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x,
				cur.y, rgbtohex(cur.color));
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
	mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x,
			start.y, rgbtohex(start.color)); //debug
}

void		drawline(t_point start, t_point end, t_window *meme, t_map *map) //start -x0y0 endx1y1
{

    start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x];
    zoomaiso(&start, &end, meme);
    if (labs(end.y - start.y) > labs(end.x - start.x))
    {
        swap(&start.x, &start.y);
        swap(&end.x, &end.y);
    }
    if (start.x > end.x)
    {
        swap(&start.y, &end.y);
        swap(&start.x, &end.x);
    }


    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float gradient;
    if (dx == 0)
        gradient = 1;
    else
        gradient = dy / dx;
    float y = start.y + gradient*(end.x - start.x);
    float x;
    t_point	cur;

    mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x,
                  end.y, rgbtohex(end.color)); // This function changes the coordinates of the machine, depending on the variable steep


    cur = start;
    y =  y + gradient;
    for (x = start.x + 1; x <= end.x - 1; x++)
    {
        if (labs(end.y - start.y) > labs(end.x - start.x))
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, y, x, rgbtohex(cur.color));
        else
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, x, y, rgbtohex(cur.color));
        cur.color = cp(cur, start, end);
        y += gradient;
    }

    mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x,
                   start.y, rgbtohex(start.color)); // The last argument - the intensity expressed as a decimal
}
*/

long int intToFixed(int value)
{
    return (value << 16);
}

long int fixedToInt(int value)
{
    if (value < 0)
        return ((value >> 16) - 1);
    else
        return (value >> 16);
}
//writes the ratio (a / b) in the format of a fixed-point numbers
int fracToFixed(int a, int b)
{
    return (a << 16) / b;
}

float  fractionalPart(int a)
{
    int  p = a - intToFixed(fixedToInt(a));
    int s = 1 << 16;
    float d = p;
    //if (d / s) throw new int;
    return d / s;
}

void    swap(long int *a, long int *b)
{
    long int t;
    t = *a;
    *a = *b;
    *b = t;
}

void drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
    float 	alpha;
    int 	dy;
    int 	dx;
    int 	intery;
    int		interx;
    int		grad;
    t_point	cur;

    //The calculation of the coordinates
    dx = (end.x > start.x) ? (end.x - start.x) : (start.x - end.x);
    dy = (end.x > start.x) ? (end.y - start.y) : (start.y - end.y);
    //If the line is parallel to one of the axis, draw an usual line - fill all the pixels in a row
    if (dx == 0) {
        if (end.y < start.y)
        {
            swap(&start.x, &end.x);
            swap(&start.y, &end.y);
        }
	cur = start;
	while (cur.y <= end.y)
	{
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1)); //i, color TODO
		cur.y++;
	}
	/*
        for (int i = start.y; i <= end.y; i++)
        {
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, i, color); //i, color TODO
        }
	*/
        return;
    }
    if (dy == 0)
    {
        if (end.x < start.x)
        {
            swap(&start.x, &end.x);
            swap(&start.y, &end.y);
        }
        for (int i = start.x; i <= end.x; i++) {
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, i, start.y, color); //i, color TODO
        }
        return;
    }
    //For the X-line (slope coefficient < 1)
    if (abs(dy) < dx)
    {
        //The first point must have a smaller x coordinate
        if (end.x < start.x)
        {
            swap(&start.x, &end.x);
            swap(&start.y, &end.y);
        }
        grad = fracToFixed(dy, dx);
        intery = intToFixed(start.y) + grad;

        //First point
        mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, color);

        for (int x = start.x + 1; x < end.x; x++)
        {
            alpha = (fractionalPart(intery));
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, x, fixedToInt(intery), rgbtohex(255 * alpha, 255 * alpha, 255 * alpha));
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, x, fixedToInt(intery) +1, (rgbtohex(255 * (1- alpha), 255 * (1 - alpha), 255 * (1 - alpha))));
            intery += grad;
        }
        //Last point
        mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, color);
    }
        //For the Y-line (slope coefficient > 1)
    else
    {
        if (end.y < start.y)
        {
            swap(&start.x, &end.x);
            swap(&start.y, &end.y);
        }
        grad = fracToFixed(dx , dy);
        interx = intToFixed(start.x) + grad;
        mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, color);
        for (int y = start.y + 1; y < end.y; y++)
        {
            alpha = (fractionalPart(interx));
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, fixedToInt(interx), y,  rgbtohex(255 * alpha, 255 * alpha, 255 * alpha));
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr,  fixedToInt(interx) + 1, y,  (rgbtohex(255 * (1 - alpha), 255 * (1 - alpha), 255 * (1 - alpha))));
            interx += grad;
        }
        mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, start.y, color);
    }
}
