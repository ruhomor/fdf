#include "fdf.h"

void				escape_map_butt(t_map *map)
{
	long int	**cell;

	if (map)
	{
		if (map->cell)
		{
			cell = map->cell;
			while (*cell)
			{
				free(*cell);
				cell++;
			}
			free(map->cell);
		}
		free(map);
		map = NULL;
	}
}

void				escape_butt(t_window *meme)
{
	t_map		*map;
	long int	*zbuf;

	if (meme)
	{
		map = meme->map;
		escape_map_butt(map);
		zbuf = meme->zbuf;
		if (zbuf)
		{
			free(zbuf);
			zbuf = NULL;
		}
		if (meme->win_ptr != NULL)
			mlx_destroy_window(meme->mlx_ptr, meme->win_ptr);
		free(meme);
		meme = NULL;
	}
	exit(0);
}

void				shufflr(t_color *rgb, unsigned char a, unsigned char b,
							unsigned char c)
{
	rgb->r = a;
	rgb->g = b;
	rgb->b = c;
}

void				wotrewot(t_color *wot, t_color hsv, unsigned char remainder)
{
	wot->r = (hsv.b * (255 - hsv.g)) >> 8;
	wot->g = (hsv.b * (255 - ((hsv.g * remainder) >> 8))) >> 8;
	wot->b = (hsv.b * (255 - ((hsv.g * (255 - remainder)) >> 8))) >> 8;
}

t_color				regionhandle(t_color wot, t_color hsv, unsigned char region)
{
	t_color rgb;

	rgb = (t_color){0, 0, 0};
	if (region == 0)
		shufflr(&rgb, hsv.b, wot.b, wot.r);
	else if (region == 1)
		shufflr(&rgb, wot.g, hsv.b, wot.r);
	else if (region == 2)
		shufflr(&rgb, wot.r, hsv.b, wot.b);
	else if (region == 3)
		shufflr(&rgb, wot.r, wot.g, hsv.b);
	else if (region == 4)
		shufflr(&rgb, wot.b, wot.r, hsv.b);
	else
		shufflr(&rgb, hsv.b, wot.r, wot.g);
	return (rgb);
}
