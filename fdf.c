/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 22:56:25 by kachiote          #+#    #+#             */
/*   Updated: 2020/02/23 22:56:27 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

int	deal_key(int key)
{
	printf("%d", key);
	return (0);
}

t_color	HsvToRgb(t_color hsv) //returns rgb
{
	t_color	rgb;
	unsigned char	region;
	unsigned char	remainder;
	unsigned char	p;
	unsigned char	q;
	unsigned char	t;

	if (hsv.g == 0)
	{
		rgb.r = hsv.b;
		rgb.g = hsv.b;
		rgb.b = hsv.b;
		return (rgb);
	}
	region = hsv.r / 43;
	remainder = (hsv.r - (region * 43)) * 6;
	p = (hsv.b * (255 - hsv.g)) >> 8;
	q = (hsv.b * (255 - ((hsv.g * remainder) >> 8))) >> 8;
	t = (hsv.b * (255 - ((hsv.g * (255 - remainder)) >> 8))) >> 8;
	if (region == 0)
	{
		rgb.r = hsv.b;
		rgb.g = t;
		rgb.b = p;
	}
	else if (region == 1)
	{
		rgb.r = q;
		rgb.g = hsv.b;
		rgb.b = p;
	}
	else if (region == 2)
	{
		rgb.r = p;
		rgb.g = hsv.b;
		rgb.b = t;
	}
	else if (region == 3)
	{
		rgb.r = p;
		rgb.g = q;
		rgb.b = hsv.b;
	}
	else if (region == 4)
	{
		rgb.r = t;
		rgb.g = p;
		rgb.b = hsv.b;
	}
	else
	{
		rgb.r = hsv.b;
		rgb.g = p;
		rgb.b = q;
	}
	return (rgb);
}

t_color RgbToHsv(t_color rgb) //returns hsv
{
    t_color hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.b = rgbMax;
    if (hsv.b == 0)
    {
        hsv.r = 0;
        hsv.g = 0;
        return hsv;
    }

    hsv.g = 255 * (int)(rgbMax - rgbMin) / hsv.b;
    if (hsv.g == 0)
    {
        hsv.r = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.r = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.r = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.r = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

/*
int interpolate(int startValue, int endValue, int stepNumber, int lastStepNumber)
{
    return (endValue - startValue) * stepNumber / lastStepNumber + startValue;
}
*/

t_color	pp(t_map *map, int x, int y, int zoom)
{
	t_color		color; //endcolor 255 0 255 //startcolor 0 255 0

	zoom--;
	zoom++;
	color.r = (130 - 0) * map->cell[y][x] / map->colorrange + 0;
	color.g = 255;
	color.b = 255;
	return (HsvToRgb(color));
}

int key_press(int keycode, void *param)
{
    t_window *meme;

    meme = (t_window *)param;
    if (keycode == 126) {
        printf("DDDDDDDDDDDDDDD");
        meme->zoom += 2;
    }
    return (0);
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;
	int	i;
	int	j;
	unsigned int	colorrange; //debug

	meme = (t_window*)malloc(sizeof(*meme));
	i = 0;
	j = 0;
	argc--;
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	//readmap(map, "test1");
	readmap(map, argv[1]);
	colorrange = map->max - map->min; //debug
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			printf("%ld ", map->cell[i][j++]);
		printf("\n");
		i++;
	}
	printf("min = %ld\n", map->min); //debug
	printf("max = %ld\n", map->max); //debug
	printf("colorrange = %d\n", colorrange); //debug
	//maperror(map); //mem debug
	meme->mlx_ptr = mlx_init();
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, 2000, 1000, "MEME");
	meme->zoom = 30;
	map->colorrange = map->max - map->min;
	drawmap(meme, map);
	mlx_expose_hook(meme->win_ptr, deal_key, NULL);
	//mlx_key_hook(meme->win_ptr, key_press, meme);
	mlx_hook(meme->win_ptr, 2, 0, key_press, meme);
	mlx_loop_hook(meme->win_ptr, deal_key, NULL);
	mlx_loop(meme->mlx_ptr);
	return (0);
}

void	drawmap(t_window *meme, t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->height - 1)
	{
		i = 0;
		while (i < map->width - 1)
		{
			drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
					(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j, 1)}, meme, map);
			drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
					(t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)}, meme, map);
			i++;
		}
		j++;
	}
	j = map->height - 1; // 1 1 1
	i = -1;		     // 1 1 1 //
	while (++i < map->width - 1)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j, 1)}, meme, map);
	i = map->width - 1;
	j = -1;
	while (++j < map->height - 1)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)}, meme, map);
}
