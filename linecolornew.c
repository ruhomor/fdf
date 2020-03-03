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

	hex = (((char)(color.r * alpha) & 0xff) << 16) | (((char)(color.g * alpha) & 0xff) << 8) | ((char)(color.b * alpha) & 0xff);
	return (hex);
}

void		zoomaiso(t_point *start, t_window *meme)
{
	int	zoom;
	double	ugol;
	t_color	bcolor;

	ugol = 0.6;

	zoom = meme->zoom; //ZOOM Section
	start->x *= zoom;
	start->y *= zoom;
	start->z *= zoom; //z -? TODO h

    start->z *= meme->attitude;
    if (meme->prjk != 1) {
        start->x -= meme->map->width / 2 * zoom;
        start->y -= meme->map->height / 2 * zoom;
    }

	bcolor = start->color; //starting point rotation
	*start = transformxyz(*start, meme->angle); //TODO zero exception??? crush
	start->color = bcolor;

	if (meme->prjk != 1) {
        start->x += meme->shift.x; //xy shift
        start->y += meme->shift.y;
    }

    if (meme->prjk == 1) {
        start->x += meme->shift.x * cos(ugol) + meme->shift.y * sin(ugol);
        start->x = (start->x - start->y) * cos(ugol); //Z-axis section
        start->y = (start->y + start->x) * sin(ugol) - start->z;
    }
}

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

void drawlinecool(t_point start, t_point end, t_window *meme, t_map *map)
{
	float	alpha;
	int	dy;
	int	dx;
	int	intery;
	int	interx;
	int	grad;
	t_point	cur;

	start.z = map->cell[start.y][start.x];
	end.z = map->cell[end.y][end.x];
	zoomaiso(&start, meme);
    zoomaiso(&end, meme);
	dx = (end.x > start.x) ? (end.x - start.x) : (start.x - end.x);
	dy = (end.x > start.x) ? (end.y - start.y) : (start.y - end.y);
	if ((dx == 0) && (start.x >= 0) && (start.x <= WINX) && (ft_min(start.y, end.y) <= WINY) && (ft_max(start.y, end.y >= 0)))
	{
		if (end.y < start.y)
			swap(&start, &end);
		cur = start;
		while (cur.y <= end.y)
		{
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cur.color, 1));
			cur.y++;
			cur.color = cpy(cur, end, start);
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
    if (abs(dy) < dx)
    {
        if (end.x < start.x)
            swap(&start, &end);
        if ((start.x <= WINX) && (end.x >= 0) && (ft_min(start.y, end.y) <= WINY) && (ft_max(start.y, end.y) >= 0)) //TODO dopisat
        {
            grad = fracToFixed(dy, dx);
            intery = intToFixed(start.y) + grad;
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

t_point pt_add(t_point a, t_point b)
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    a.color.r = a.color.r + b.color.r;
    a.color.g = a.color.g + b.color.g;
    a.color.b = a.color.b + b.color.b;
    return (a);
}

t_fpoint pt_fadd(t_fpoint a, t_fpoint b)
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    a.color.r = a.color.r + b.color.r;
    a.color.g = a.color.g + b.color.g;
    a.color.b = a.color.b + b.color.b;
    return (a);
}

t_point pt_sub(t_point a, t_point b)
{
    a.x = a.x - b.x;
    a.y = a.y - b.y;
    a.z = a.z - b.z;
    a.color.r = a.color.r - b.color.r;
    a.color.g = a.color.g - b.color.g;
    a.color.b = a.color.b - b.color.b;
    return (a);
}

t_point pt_mult(t_point a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.color.r *= b;
    a.color.g *= b;
    a.color.b *= b;
    return (a);
}

t_fpoint pt_fmult(t_fpoint a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.color.r *= b;
    a.color.g *= b;
    a.color.b *= b;
    return (a);
}

t_fpoint pt_ltf(t_point a)
{
    t_fpoint b;

    b.x = (float)a.x;
    b.y = (float)a.y;
    b.z = (float)a.z;
    b.color.r = (float)a.color.r;
    b.color.g = (float)a.color.g;
    b.color.b = (float)a.color.b;
    return (b);
}

t_point pt_ftl(t_fpoint a)
{
    t_point b;

    b.x = (long int)a.x;
    b.y = (long int)a.y;
    b.z = (long int)a.z;
    b.color.r = (unsigned char)a.color.r;
    b.color.g = (unsigned char)a.color.g;
    b.color.b = (unsigned char)a.color.b;
    return (b);
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
        a.x = round(t0.x + ((float)(t2.x - t0.x)) * alpha);
        b.x = second_half ? round(t1.x + ((float)(t2.x - t1.x)) * beta) : round(t0.x + ((float)(t1.x - t0.x)) * beta);
        a.y = round(t0.y + ((float)(t2.y - t0.y)) * alpha);
        b.y = second_half ? round(t1.y + ((float)(t2.y - t1.y)) * beta) : round(t0.y + ((float)(t1.y - t0.y)) * beta);
        a.z = round(t0.z + ((float)(t2.z - t0.z)) * alpha);
        b.z = second_half ? round(t1.z + ((float)(t2.z - t1.z)) * beta) : round(t0.z + ((float)(t1.z - t0.z)) * beta);
        a.color.r = round(t0.color.r + ((float)(t2.color.r - t0.color.r)) * alpha);
        b.color.r = second_half ? round(t1.color.r + ((float)(t2.color.r - t1.color.r)) * beta) : round(t0.color.r + ((float)(t1.color.r - t0.color.r)) * beta);
        a.color.g = round(t0.color.g + ((float)(t2.color.g - t0.color.g)) * alpha);
        b.color.g = second_half ? round(t1.color.g + ((float)(t2.color.g - t1.color.g)) * beta) : round(t0.color.g + ((float)(t1.color.g - t0.color.g)) * beta);
        a.color.b = round(t0.color.b + ((float)(t2.color.b - t0.color.b)) * alpha);
        b.color.b = second_half ? round(t1.color.b + ((float)(t2.color.b - t1.color.b)) * beta) : round(t0.color.b + ((float)(t1.color.b - t0.color.b)) * beta);
        if (a.x > b.x)
            swap(&a, &b);
        j = a.x;
        while (j <= b.x)
        {
            phi = b.x == a.x ? 1. : (float)(j - a.x) / (float)(b.x - a.x);
            //cur = (float)a + ((float)(b - a)) * phi;
            cur.x = round((float)a.x + ((float)(b.x - a.x)) * phi);
            cur.y = round((float)a.y + ((float)(b.y - a.y)) * phi);
            cur.z = round((float)a.z + ((float)(b.z - a.z)) * phi);
            cur.color.r = round((float)a.color.r + ((float)(b.color.r - a.color.r)) * phi);
            cur.color.g = round((float)a.color.g + ((float)(b.color.g - a.color.g)) * phi);
            cur.color.b = round((float)a.color.b + ((float)(b.color.b - a.color.b)) * phi);
            idx = cur.x + cur.y * WINX;
            if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINX) && (cur.y < WINY) && (zbuf[idx] <= cur.z))
            {
                //printf("idx: %ld zbuf: %ld x: %ld y: %ld z: %ld\n", idx, zbuf[idx], cur.x, cur.y, cur.z);
                zbuf[idx] = cur.z;
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cpx(cur, a, b), 1));
                //image.set(P.x, P.y, color);
            }
            j++;
        }
        i++;
    }
}

void drawline(t_point start, t_point end, t_window *meme, t_map *map)
{
    long int	j;
    t_point     cur;
    float       phi;
    long int    idx;
    long int    *zbuf;
    char        steep;
    long int    dx;
    long int    dy;
    long int    derror2;
    long int    error2;

    zbuf = meme->zbuf;
    start.z = map->cell[start.y][start.x]; //zoom?
    end.z = map->cell[end.y][end.x]; //zoom? //zoom?
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
        swap(&start, &end);
    dx = end.x - start.x;
    dy = end.y - start.y;
    derror2 = labs(dy) * 2;
    error2 = 0;
    j = start.x;
    while (j <= end.x)
    {
        phi = end.x == start.x ? 1. : (float)(j - start.x) / (float)(end.x - start.x);
        //cur = (float)a + ((float)(b - a)) * phi;
        cur.x = round((float)start.x + ((float)(end.x - start.x)) * phi);
        cur.y = round((float)start.y + ((float)(end.y - start.y)) * phi);
        cur.z = round((float)start.z + ((float)(end.z - start.z)) * phi);
        cur.color.r = round((float)start.color.r + ((float)(end.color.r - start.color.r)) * phi);
        cur.color.g = round((float)start.color.g + ((float)(end.color.g - start.color.g)) * phi);
        cur.color.b = round((float)start.color.b + ((float)(end.color.b - start.color.b)) * phi);
        if (steep) //swapped x and y ! ! ! and it has to be that way ! ! !
        {
            idx = cur.y + cur.x * WINX; //TODO think here DEBUG POLICE!
            if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINY) && (cur.y < WINX) && (zbuf[idx] <= cur.z))
            {
                zbuf[idx] = cur.z; // this somehow doesnt seem to be working!!!
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.y, cur.x, rgbtohex(cpx(cur, start, end), 1));
            }
        }
        else
        {
            idx = cur.x + cur.y * WINX;// TODO and here DEBUG PLS
            if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINX) && (cur.y < WINY) && (zbuf[idx] <= cur.z))
            {
                zbuf[idx] = cur.z;// this too! somehow doesnt seem to be working!!!
                mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y, rgbtohex(cpy(cur, start, end), 1));
            }
        }
        error2 += derror2;
        if (error2 > dx)
        {
            cur.y += (end.y > start.y ? 1 : -1);
            error2 -= dx * 2;
        }
        cur.x++;
        j++;
    }
}