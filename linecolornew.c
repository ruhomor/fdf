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
	hex = (((char)(color.r * alpha) & 0xff) << 16) | (((char)(color.g * alpha) & 0xff) << 8) | ((char)(color.b * alpha) & 0xff);
	return (hex);
}

void		zoomaiso(t_point *start, t_window *meme)
{
	int	zoom;
	double	ugol;
	t_color	bcolor;

	ugol = 0.5;

	zoom = meme->zoom; //ZOOM Section
	start->x *= zoom;
	start->y *= zoom;
	start->z *= zoom; //z -? TODO h
//	end->x *= zoom;
//	end->y *= zoom;
//	end->z *= zoom; //z -? TODO h

    start->z *= meme->attitude;
 //   end->z *= meme->attitude;

//	end->x -= meme->map->width / 2 * zoom;
//	end->y -= meme->map->height / 2 * zoom;
	start->x -= meme->map->width / 2 * zoom;
	start->y -= meme->map->height / 2 * zoom;

	bcolor = start->color; //starting point rotation
	*start = transformXYZ(*start, meme->angle); //TODO zero exception??? crush
	start->color = bcolor;

//	bcolor = end->color; //ending point rotation
//	*end = transformXYZ(*end, meme->angle); //bred bug
//	end->color = bcolor;

	start->x += meme->shift.x; //xy shift
	start->y += meme->shift.y;
//	end->x += meme->shift.x;
//	end->y += meme->shift.y;
/*
	start->x = (start->x - start->y) * cos(ugol); //Z-axis section
	start->y = (start->y + start->x) * sin(ugol) - start->z;
	end->x = (end->x - end->y) * cos(ugol);
	end->y = (end->y + end->x) * sin(ugol) - end->z;
*/
}

t_color		cpx(t_point cur, t_point start, t_point end)
{
	t_color	color;

	if (end.x != start.x)
	{
		color.r = start.color.r + (end.color.r - start.color.r) * (cur.x - start.x) / (end.x - start.x);
		color.g = start.color.g + (end.color.g - start.color.g) * (cur.x - start.x) / (end.x - start.x);
		color.b = start.color.b + (end.color.b - start.color.b) * (cur.x - start.x) / (end.x - start.x);
	}
	else
	    {
        color.r = start.color.r;
        color.g = start.color.g;
        color.b = start.color.b;
    }
	return (color);
}

t_color		cpy(t_point cur, t_point start, t_point end)
{
    t_color	color;

     if (end.y != start.y)
    {
        color.r = start.color.r + (end.color.r - start.color.r) * (cur.y - start.y) / (end.y - start.y);
        color.g = start.color.g + (end.color.g - start.color.g) * (cur.y - start.y) / (end.y - start.y);
        color.b = start.color.b + (end.color.b - start.color.b) * (cur.y - start.y) / (end.y - start.y);
    }
    else {
        color.r = start.color.r;
        color.g = start.color.g;
        color.b = start.color.b;
    }
    return (color);
}

t_color		cpz(t_point cur, t_point start, t_point end)
{
    t_color	color;

    if (end.z != start.z)
    {
        color.r = start.color.r + (end.color.r - start.color.r) * (cur.z - start.z) / (end.z - start.z);
        color.g = start.color.g + (end.color.g - start.color.g) * (cur.z - start.z) / (end.z - start.z);
        color.b = start.color.b + (end.color.b - start.color.b) * (cur.z - start.z) / (end.z - start.z);
    }
    else {
        color.r = start.color.r;
        color.g = start.color.g;
        color.b = start.color.b;
    }
    return (color);
}

void	swap(t_point *a, t_point *b)
{
	t_point t;

	t = *a;
	*a = *b;
	*b = t;
}

void    swapxy(long int *a, long int *b)
{
    long int c;

    c = *a;
    *a = *b;
    *b = c;
}

long int    ft_min(long int a, long int b)
{
    if (a > b)
        return (b);
    return (a);
}

long int    ft_max(long int a, long int b)
{
    if (a > b)
        return (a);
    return (b);
}
/*
void drawlinecool(t_point start, t_point end, t_window *meme, t_map *map)
{
	float	alpha;
	int	dy;
	int	dx;
	int	intery;
	int	interx;
	int	grad;
	t_point	cur;

	start.z = map->cell[start.y][start.x]; //zoom?
	end.z = map->cell[end.y][end.x]; //zoom?
	zoomaiso(&start, &end, meme);
    //The calculation of the coordinates
	dx = (end.x > start.x) ? (end.x - start.x) : (start.x - end.x);
	dy = (end.x > start.x) ? (end.y - start.y) : (start.y - end.y);
    //If the line is parallel to one of the axis, draw an usual line - fill all the pixels in a row
	if ((dx == 0) && (start.x >= 0) && (start.x <= WINX) && (ft_min(start.y, end.y) <= WINY) && (ft_max(start.y, end.y >= 0)))
	{
		if (end.y < start.y)
			swap(&start, &end);
		cur = start;
		while (cur.y <= end.y)
		{
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1)); //i, color TODO
			cur.y++;
			cur.color = cpy(cur, end, start); //>>>>>TODO
		}
	    return ;
    }
    if (dy == 0 && (start.y >= 0) && (start.y <= WINY) && (ft_min(start.x, end.x) <= WINX) && (ft_max(start.x, end.x) >= 0))
    {
        if (end.x < start.x)
            swap(&start, &end);
	cur = start;
	while (cur.x <= end.x)
	{
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1));
		cur.x++;
		cur.color = cpx(cur, start, end);
	}
	    return ;
    }
    //For the X-line (slope coefficient < 1)
    if (abs(dy) < dx)
    {
        //The first point must have a smaller x coordinate
        if (end.x < start.x)
            swap(&start, &end);
        if ((start.x <= WINX) && (end.x >= 0) && (ft_min(start.y, end.y) <= WINY) && (ft_max(start.y, end.y) >= 0)) //TODO dopisat
        {
            grad = fracToFixed(dy, dx);
            intery = intToFixed(start.y) + grad;
            //First point
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, rgbtohex(start.color, 1));
            cur = start;
            cur.x++;
            while (cur.x < end.x)
            {
                alpha = (fractionalPart(intery));
                cur.y = fixedToInt(intery);
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1 - alpha));
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y + 1, (rgbtohex(cur.color, alpha)));
                intery += grad;
                cur.x++;
                cur.color = cpx(cur, start, end);
            }
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, rgbtohex(end.color, 1));
        }
    }
        //For the Y-line (slope coefficient > 1)
    else {
        if (end.y < start.y)
            swap(&start, &end);
        if ((start.y <= WINY) && (end.y >= 0) && (ft_min(start.x, end.x) <= WINX) && (ft_max(start.x, end.x) >= 0)) //TODO dopisat
        {
            grad = fracToFixed(dx, dy);
            interx = intToFixed(start.x) + grad;
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, start.x, start.y, rgbtohex(start.color, 1));
            cur = start;
            cur.y++;
            while (cur.y < end.y) {
                alpha = (fractionalPart(interx));
                cur.x = fixedToInt(interx);
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1 - alpha));
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x + 1, cur.y, rgbtohex(cur.color, alpha));
                interx += grad;
                cur.y++;
                cur.color = cpy(cur, start, end);
            }
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, end.x, end.y, rgbtohex(end.color, 1)); //end.y - start.y?
        }
    }
}
*/
void drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
    char steep;
    int dx;
    int dy;
    int derror2;
    int error2;
    t_point cur;

    start.z = map->cell[start.y][start.x]; //zoom?
    end.z = map->cell[end.y][end.x]; //zoom?
    zoomaiso(&start, meme);
    zoomaiso(&end, meme);
    steep = 0;
    if (labs(start.x - end.x) < labs(start.y - end.y))
    {
      swapxy(&start.x, &start.y);
      swapxy(&end.x, &end.y);
      steep = 1;
    }
    if (start.x > end.x)
    {
        swap(&start, &end);
    }
    dx = end.x - start.x;
    dy = end.y - start.y;
    derror2 = abs(dy) * 2;
    error2 = 0;
    cur = start;
    while (cur.x <= end.x)
    {
        if (steep) 
        {
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.y, cur.x, rgbtohex(cur.color, 1));
            //image.set(y, x, color);
            cur.color = cpx(cur, start, end);
        } 
        else
        {
            //image.set(x, y, color);
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1));
            cur.color = cpy(cur, start, end);
        }
        error2 += derror2;
        if (error2 > dx) 
        {
            cur.y += (end.y > start.y ? 1 : -1);
            error2 -= dx * 2;
        }
        cur.x++;
    }
}

void triangle1(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map)
{
    int         total_height;
    long int    i;
    t_point     a;
    t_point     b;
    char        second_half;
    int         segment_height;
    float       alpha;
    float       beta;
    long int    j;

    t0.z = map->cell[t0.y][t0.x]; //zoom?
    t1.z = map->cell[t1.y][t1.x]; //zoom? //zoom?
    t2.z = map->cell[t2.y][t2.x]; //zoom?
    zoomaiso(&t0, meme);
    zoomaiso(&t1, meme);
    zoomaiso(&t2, meme);

    if (t0.y == t1.y && t0.y == t2.y)
        return ; // i dont care about degenerate triangles
        // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (t0.y > t1.y)
        swap(&t0, &t1);
    if (t0.y > t2.y)
        swap(&t0, &t2);
    if (t1.y > t2.y)
        swap(&t1, &t2);
    total_height = t2.y - t0.y;
    i = 0;
    while(i < total_height)
    {
        second_half = i > t1.y - t0.y || t1.y == t0.y;
        segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        alpha = (float)i / total_height;
        beta  = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
        a.x = t0.x + (t2.x - t0.x) * alpha;
        b.x = second_half ? t1.x + (t2.x - t1.x) * beta : t0.x + (t1.x - t0.x) * beta;
        a.y = t0.y + (t2.y - t0.y) * alpha;
        b.y = second_half ? t1.y + (t2.y - t1.y) * beta : t0.y + (t1.y - t0.y) * beta;
        a.color.g = t0.color.g + (t2.color.g - t0.color.g) * alpha;
        b.color.g = second_half ? t1.color.g + (t2.color.g - t1.color.g) * beta : t0.color.g + (t1.color.g - t0.color.g) * beta;
        a.color.b = t0.color.b + (t2.color.b - t0.color.b) * alpha;
        b.color.b = second_half ? t1.color.b + (t2.color.b - t1.color.b) * beta : t0.color.b + (t1.color.b - t0.color.b) * beta;
        a.color.r = t0.color.r + (t2.color.r - t0.color.r) * alpha;
        b.color.r = second_half ? t1.color.r + (t2.color.r - t1.color.r) * beta : t0.color.r + (t1.color.r - t0.color.r) * beta;
        if (a.x > b.x)
            swap(&a, &b);
        j = a.x;
        while (j <= b.x)
        {
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, j, t0.y + i, rgbtohex(cpy((t_point){.x = j, .y = t0.y + i}, a, b), 1)); // attention, due to int casts t0.y+i != A.y
            j++;
        }
        i++;
    }
}

void triangle2(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map)
{
    int         total_width;
    long int    i;
    t_point     a;
    t_point     b;
    char        second_half;
    int         segment_width;
    float       alpha;
    float       beta;
    long int    j;

    t0.z = map->cell[t0.y][t0.x]; //zoom?
    t1.z = map->cell[t1.y][t1.x]; //zoom? //zoom?
    t2.z = map->cell[t2.y][t2.x]; //zoom?
    zoomaiso(&t0, meme);
    zoomaiso(&t1, meme);
    zoomaiso(&t2, meme);

    if (t0.x == t1.x && t0.x == t2.x)
        return ; // i dont care about degenerate triangles
    // sort the vertices, t0, t1, t2 lower-to-upper (bubblesort yay!)
    if (t0.x > t1.x)
        swap(&t0, &t1);
    if (t0.x > t2.x)
        swap(&t0, &t2);
    if (t1.x > t2.x)
        swap(&t1, &t2);
    total_width = t2.x - t0.x;
    i = 0;
    while(i < total_width)
    {
        second_half = i > t1.x - t0.x || t1.x == t0.x;
        segment_width = second_half ? t2.x - t1.x : t1.x - t0.x;
        alpha = (float)i / total_width;
        beta  = (float)(i - (second_half ? t1.x - t0.x : 0)) / segment_width; // be careful: with above conditions no division by zero here
        a.x = t0.x + (t2.x - t0.x) * alpha;
        b.x = second_half ? t1.x + (t2.x - t1.x) * beta : t0.x + (t1.x - t0.x) * beta;
        a.y = t0.y + (t2.y - t0.y) * alpha;
        b.y = second_half ? t1.y + (t2.y - t1.y) * beta : t0.y + (t1.y - t0.y) * beta;
        a.z = t0.z + (t2.z - t0.z) * alpha;
        b.z = second_half ? t1.z + (t2.z - t1.z) * beta : t0.z + (t1.z - t0.z) * beta;
        a.color.g = t0.color.g + (t2.color.g - t0.color.g) * alpha;
        b.color.g = second_half ? t1.color.g + (t2.color.g - t1.color.g) * beta : t0.color.g + (t1.color.g - t0.color.g) * beta;
        a.color.b = t0.color.b + (t2.color.b - t0.color.b) * alpha;
        b.color.b = second_half ? t1.color.b + (t2.color.b - t1.color.b) * beta : t0.color.b + (t1.color.b - t0.color.b) * beta;
        a.color.r = t0.color.r + (t2.color.r - t0.color.r) * alpha;
        b.color.r = second_half ? t1.color.r + (t2.color.r - t1.color.r) * beta : t0.color.r + (t1.color.r - t0.color.r) * beta;
        if (a.y > b.y)
            swap(&a, &b);
        j = a.y;
        while (j <= b.y)
        {
            mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, t0.x + i, j, rgbtohex(cpx((t_point){.x = t0.x + i, .y = j}, a, b), 1)); // attention, due to int casts t0.y+i != A.y TODO cpz??
            j++;
        }
        i++;
    }
}

void trianglebuf(t_point t0, t_point t1, t_point t2, t_window *meme, t_map *map)
{
	long int	total_height;
	long int	i;
	long int	j;
	char		second_half;
	long int	segment_height;
	float		alpha;
    float       beta;
    t_point     a;
    t_point     b;
    t_point     cur;
    float       phi;
    long int    idx;
    long int    *zbuf;

    zbuf = meme->zbuf;
    t0.z = map->cell[t0.y][t0.x]; //zoom?
    t1.z = map->cell[t1.y][t1.x]; //zoom? //zoom?
    t2.z = map->cell[t2.y][t2.x]; //zoom?
    zoomaiso(&t0, meme);
    zoomaiso(&t1, meme);
    zoomaiso(&t2, meme);

    if (t0.y == t1.y && t0.y == t2.y)
        return ; // i dont care about degenerate triangles
    if (t0.y > t1.y)
        swap(&t0, &t1);
    if (t0.y > t2.y)
        swap(&t0, &t2);
    if (t1.y > t2.y)
        swap(&t1, &t2);
    total_height = t2.y - t0.y;
    i = 0;
    while (i < total_height)
    {
        second_half = i > t1.y - t0.y || t1.y == t0.y;
        segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        alpha = (float)i / total_height;
        beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
        //Vec3i A =               t0 + Vec3f(t2-t0)*alpha;
        //Vec3i B = second_half ? t1 + Vec3f(t2-t1)*beta : t0 + Vec3f(t1-t0)*beta;
        a.x = t0.x + ((float)(t2.x - t0.x)) * alpha;
        b.x = second_half ? t1.x + ((float)(t2.x - t1.x)) * beta : t0.x + ((float)(t1.x - t0.x)) * beta;
        a.y = t0.y + ((float)(t2.y - t0.y)) * alpha;
        b.y = second_half ? t1.y + ((float)(t2.y - t1.y)) * beta : t0.y + ((float)(t1.y - t0.y)) * beta;
        a.z = t0.z + ((float)(t2.z - t0.z)) * alpha;
        b.z = second_half ? t1.z + ((float)(t2.z - t1.z)) * beta : t0.z + ((float)(t1.z - t0.z)) * beta;
        a.color.r = t0.color.r + ((float)(t2.color.r - t0.color.r)) * alpha;
        b.color.r = second_half ? t1.color.r + ((float)(t2.color.r - t1.color.r)) * beta : t0.color.r + ((float)(t1.color.r - t0.color.r)) * beta;
        a.color.g = t0.color.g + ((float)(t2.color.g - t0.color.g)) * alpha;
        b.color.g = second_half ? t1.color.g + ((float)(t2.color.g - t1.color.g)) * beta : t0.color.g + ((float)(t1.color.g - t0.color.g)) * beta;
        a.color.b = t0.color.b + ((float)(t2.color.b - t0.color.b)) * alpha;
        b.color.b = second_half ? t1.color.b + ((float)(t2.color.b - t1.color.b)) * beta : t0.color.b + ((float)(t1.color.b - t0.color.b)) * beta;
        if (a.x > b.x)
            swap(&a, &b);
        j = a.x;
        while (j <= b.x)
        {
            phi = b.x == a.x ? 1. : (float)(j - a.x) / (float)(b.x - a.x);
            //cur = (float)a + ((float)(b - a)) * phi;
            cur.x = (float)a.x + ((float)(b.x - a.x)) * phi;
            cur.y = (float)a.y + ((float)(b.y - a.y)) * phi;
            cur.z = (float)a.z + ((float)(b.z - a.z)) * phi;
            cur.color.r = (float)a.color.r + ((float)(b.color.r - a.color.r)) * phi;
            cur.color.g = (float)a.color.g + ((float)(b.color.g - a.color.g)) * phi;
            cur.color.b = (float)a.color.b + ((float)(b.color.b - a.color.b)) * phi;
            idx = cur.x + cur.y * WINX;
            if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINX) && (cur.y < WINY) && (zbuf[idx] < cur.z))
            {
		    printf("idx: %ld", idx);
                zbuf[idx] = cur.z;
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cpx(cur, a, b), 1));
                //image.set(P.x, P.y, color);
            }
            j++;
        }
        i++;
    }
}
