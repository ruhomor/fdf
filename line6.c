#include "fdf.h"

unsigned char	ac(char s, t_color tr, float beta)
{
	unsigned char ans;

	ans = s ? iac(tr.g, tr.b, beta) : iac(tr.r, tr.g, beta);
	return (ans);
}

t_line			trianglearsehole(t_point t0, t_point t1, t_point t2,
								   t_2dpoint ass)
{
	float		alpha;
	float		beta;
	t_line		line;
	char		s;
	long int	segment;

	s = ass.x > t1.y - t0.y || t1.y == t0.y;
	segment = s ? t2.y - t1.y : t1.y - t0.y;
	alpha = (float)ass.x / ass.y;
	beta = (float)(ass.x - (s ? t1.y - t0.y : 0)) / segment;
	line.a.x = iai(t0.x, t2.x, alpha);
	line.b.x = s ? iai(t1.x, t2.x, beta) : iai(t0.x, t1.x, beta);
	line.a.y = iai(t0.y, t2.y, alpha);
	line.b.y = s ? iai(t1.y, t2.y, beta) : iai(t0.y, t1.y, beta);
	line.a.z = iai(t0.z, t2.z, alpha);
	line.b.z = s ? iai(t1.z, t2.z, beta) : iai(t0.z, t1.z, beta);
	line.a.color.r = iac(t0.color.r, t2.color.r, alpha);
	line.b.color.r = ac(s, (t_color){t0.color.r, t1.color.r, t2.color.r}, beta);
	line.a.color.g = iac(t0.color.g, t2.color.g, alpha);
	line.b.color.g = ac(s, (t_color){t0.color.g, t1.color.g, t2.color.g}, beta);
	line.a.color.b = iac(t0.color.b, t2.color.b, alpha);
	line.b.color.b = ac(s, (t_color){t0.color.b, t1.color.b, t2.color.b}, beta);
	return (line);
}

long int		*initsortbuf(t_point *t0, t_point *t1, t_point *t2,
							 t_window *meme)
{
	t_map		*map;

	map = meme->map;
	t0->z = map->cell[t0->y][t0->x];
	t1->z = map->cell[t1->y][t1->x];
	t2->z = map->cell[t2->y][t2->x];
	zoomaiso(t0, meme);
	zoomaiso(t1, meme);
	zoomaiso(t2, meme);
	if (t0->y == t1->y && t0->y == t2->y)
		return (NULL);
	if (t0->y > t1->y)
		swap(t0, t1);
	if (t0->y > t2->y)
		swap(t0, t2);
	if (t1->y > t2->y)
		swap(t1, t2);
	return (meme->zbuf);
}

void			trgg(t_line line, int j, long int *zbuf, t_window *meme)
{
	float		phi;
	t_point		cur;
	long int	idx;

	phi = line.b.x == line.a.x ? 1. :
		  (float)(j - line.a.x) / (float)(line.b.x - line.a.x);
	cur.x = iai(line.a.x, line.b.x, phi);
	cur.y = iai(line.a.y, line.b.y, phi);
	cur.z = iai(line.a.z, line.b.z, phi);
	cur.color.r = iac(line.a.color.r, line.b.color.r, phi);
	cur.color.g = iac(line.a.color.g, line.b.color.g, phi);
	cur.color.b = iac(line.a.color.b, line.b.color.b, phi);
	idx = cur.x + cur.y * WINX;
	if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINX) &&
		(cur.y < WINY) && (zbuf[idx] <= cur.z))
	{
		zbuf[idx] = cur.z;
		mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
					  rgbtohex(cpx(cur, line.a, line.b), 1));
	}
}

void			trianglebuf(t_point t0, t_point t1, t_point t2, t_window *meme)
{
	int			total_h;
	int			i;
	int			j;
	t_line		line;
	long int	*zbuf;

	if ((zbuf = initsortbuf(&t0, &t1, &t2, meme)) == NULL)
		return ;
	total_h = t2.y - t0.y;
	i = 0;
	while (i < total_h)
	{
		line = trianglearsehole(t0, t1, t2, (t_2dpoint){.x = i, .y = total_h});
		if (line.a.x > line.b.x)
			swap(&line.a, &line.b);
		j = line.a.x;
		while (j <= line.b.x)
		{
			trgg(line, j, zbuf, meme);
			j++;
		}
		i++;
	}
}
