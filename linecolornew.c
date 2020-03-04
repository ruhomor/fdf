#include "fdf.h"

void			stiptip(char steep, t_point cur, t_window *meme, t_line line)
{
	long int	idx;

	if (steep)
	{
		idx = cur.y + cur.x * WINX;
		if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINY) &&
			(cur.y < WINX) && (meme->zbuf[idx] <= cur.z))
		{
			meme->zbuf[idx] = cur.z;
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.y, cur.x,
					rgbtohex(cpx(cur, line.a, line.b), 1));
		}
	}
	else
	{
		idx = cur.x + cur.y * WINX;
		if ((cur.x >= 0) && (cur.y >= 0) && (cur.x < WINX) &&
			(cur.y < WINY) && (meme->zbuf[idx] <= cur.z))
		{
			meme->zbuf[idx] = cur.z;
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, cur.x, cur.y,
					rgbtohex(cpy(cur, line.a, line.b), 1));
		}
	}
}

char			boomer(t_window *meme, t_2dline *lain, t_point *start,
		t_point *end)
{
	char	steep;

	start->z = meme->map->cell[start->y][start->x];
	end->z = meme->map->cell[end->y][end->x];
	zoomaiso(start, meme);
	zoomaiso(end, meme);
	steep = 0;
	if (labs(start->x - end->x) < labs(start->y - end->y))
	{
		swapxy(&start->x, &start->y);
		swapxy(&end->x, &end->y);
		steep = 1;
	}
	if (start->x > end->x)
		swap(start, end);
	lain->d.x = end->x - start->x;
	lain->d.y = end->y - start->y;
	lain->e.x = labs(lain->d.y) * 2;
	lain->e.y = 0;
	return (steep);
}

void			drawline(t_point start, t_point end, t_window *meme)
{
	t_point		cur;
	char		steep;
	t_2dline	lain;
	t_ass		bass;

	steep = boomer(meme, &lain, &start, &end);
	bass.j = start.x - 1;
	while (++bass.j <= end.x)
	{
		bass.phi = end.x == start.x ? 1. : (float)(bass.j - start.x) /
				(float)(end.x - start.x);
		cur.x = iai(start.x, end.x, bass.phi);
		cur.y = iai(start.y, end.y, bass.phi);
		cur.z = iai(start.z, end.z, bass.phi);
		cur.color.r = iac(start.color.r, end.color.r, bass.phi);
		cur.color.g = iac(start.color.g, end.color.g, bass.phi);
		cur.color.b = iac(start.color.b, end.color.b, bass.phi);
		stiptip(steep, cur, meme, (t_line){start, end});
		lain.e.y += lain.e.x;
		if (lain.e.y > lain.d.x)
		{
			cur.y += (end.y > start.y ? 1 : -1);
			lain.e.y -= lain.d.x * 2;
		}
	}
}
