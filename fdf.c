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
	t_color		hsv;
	unsigned char	rgbMin;	
	unsigned char	rgbMax;

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

t_point ft_xy(int x, int y)
{
    static t_point point0 = {0, 0, 0, {0, 0, 0}};
    static t_point point;
    point = point0;
    point0.x = x;
    point0.y = y;
    return (point);
}

int	mouse_move(int x, int y, void *p)
{
	t_window	*meme;
	t_point     point;
	double      da;
	double      db;

	meme = (t_window*)p;
	point = ft_xy(x, y);
	db = (point.x != 0) ? (double)(x - point.x) / point.x : 0;
	da = (point.y != 0) ? (double)(y - point.y) / point.y : 0;
	if (meme->drag_flag == 1)
	{
		printf("Dragging in MEME, at %dx%d %fx%f.\n", x, y, da, db);
        meme->angle.a += da;
        meme->angle.b += db;
        mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
        drawmap(meme, meme->map);
	}
	return (0);
}

int	mouse_press(int button, int x, int y, void *p)
{
	t_window	*meme;

	meme = (t_window*)p;
	printf("Pressed in MEME, button %d at %dx%d.\n", button, x, y);
	if (button == 1)
	{
		meme->drag_flag = 1;
		ft_xy(x, y);
	}
    if (button == 4) //scroll up
    {
        meme->zoom += 1;
        mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
        drawmap(meme, meme->map);
    }
    if (button == 5) //scroll down
    {
        meme->zoom -= 1;
        mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
        drawmap(meme, meme->map);

    }
	return (0);
}

int	mouse_release(int button, int x, int y, void *p)
{
	t_window	*meme;

	meme = (t_window*)p;
	printf("Released in MEME, button %d at %dx%d.\n", button, x, y);
	if (button == 1)
	{
		meme->drag_flag = 0;
	}
	return (0);
}

t_point	transformX(t_point point, double angle)
{
	t_point	tmp;

	tmp.x = point.x;
	tmp.y = point.y * cos(angle) + point.z * sin(angle);
	tmp.z = -point.y * sin(angle) + point.z * cos(angle);
	return (tmp);
}

t_point	transformY(t_point point, double angle)
{
	t_point	tmp;

	tmp.x = point.x * cos(angle) + point.z * sin(angle);
	tmp.y = point.y;
	tmp.z = -point.x * sin(angle) + point.z * cos(angle);
	return (tmp);
}
/*
t_point	transformZ(t_point point, double angle)
{
	t_point	tmp;

	tmp.x = point.x * cos(angle) - point.y * sin(angle);
	tmp.y = point.x * sin(angle) + point.y * cos(angle);
	tmp.z = point.z;
	return (tmp);
}
*/
t_point transformXYZ(t_point point, t_angle angle)
{
	return (transformY(transformX(point, angle.a), angle.b));
}

int	key_press1(int keycode, void *p)
{
	t_window	*meme;

	meme = (t_window*)p;
	if (keycode == 126) //up
	{
        meme->shift.u_flag = (meme->shift.u_flag == 1) ? 0 : -1;
		printf("shifty change = %ld\n", meme->shift.y);
	}
	if (keycode == 125) //down
	{
        meme->shift.d_flag = (meme->shift.d_flag == -1) ? 0 : 1;
		printf("shifty change = %ld\n", meme->shift.y);
	}
	if (keycode == 124) //right
	{
        meme->shift.r_flag = (meme->shift.r_flag == -1) ? 0 : 1;
		printf("shiftx change = %ld\n", meme->shift.x);
	}
	if (keycode == 123) //left
	{
		meme->shift.l_flag = (meme->shift.l_flag == 1) ? 0 : -1;
		printf("shiftx change = %ld\n", meme->shift.x);
	}
	if (keycode == 69)
    {
	    meme->attitude += 1;
    }
	if (keycode == 78)
    {
	    meme->attitude -= 1;
    }
	meme->shift.x += meme->shift.r_flag + meme->shift.l_flag; //TODO put inside if
	meme->shift.y += meme->shift.u_flag + meme->shift.d_flag;
	mlx_clear_window(meme->mlx_ptr, meme->win_ptr);
	drawmap(meme, meme->map);
	return (0);
}

int	key_release1(int keycode, void *p)
{
    t_window	*meme;

    meme = (t_window*)p;
    if (keycode == 126) //up
    {
        meme->shift.u_flag = (meme->shift.u_flag == -1) ? 0 : 1;
        printf("shifty change = %ld\n", meme->shift.y);
    }
    if (keycode == 125) //down
    {
        meme->shift.d_flag = (meme->shift.d_flag == 1) ? 0 : -1;
        printf("shifty change = %ld\n", meme->shift.y);
    }
    if (keycode == 124) //right
    {
        meme->shift.r_flag = (meme->shift.r_flag == 1) ? 0 : -1;
        printf("shiftx change = %ld\n", meme->shift.x);
    }
    if (keycode == 123) //left
    {
        meme->shift.l_flag = (meme->shift.l_flag == -1) ? 0 : 1;
        printf("shiftx change = %ld\n", meme->shift.x);
    }
    return (0);
}

void    initbuf(long int *arr, long int size)
{
    long int    i;

    i = -1;
    while (++i < size)
        *arr++ = MIN;
}

int	main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;
	int	i;
	int	j;
	unsigned int	colorrange; //debug

	meme = (t_window*)malloc(sizeof(*meme));
    meme->zbuf = (long int*)malloc(WINY * WINX * sizeof(*(meme->zbuf))); //TODO free on exit
    initbuf(meme->zbuf, WINX * WINY);
	meme->drag_flag = 0;
	meme->shift.r_flag = 0;
	meme->shift.l_flag = 0;
    meme->shift.u_flag = 0;
    meme->shift.d_flag = 0;
	meme->angle.a = 0;
	meme->angle.b = 0;
	meme->zoom = 2;
	meme->attitude = 1;
	i = 0;
	j = 0;
	argc--;
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	//readmap(map, "test1");
	readmap(map, argv[1]);
    meme->shift.x = WINX / 2 - map->width / 2;
    meme->shift.y = WINY / 2 - map->height / 2;
	colorrange = map->max - map->min; //debug TODO BUG
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
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, WINX, WINY, "MEME");
	map->colorrange = map->max - map->min; //colorrange zero TODO BUG

	meme->map = map;
	drawmap(meme, map);
	//mlx_mouse_hook(meme->win_ptr, mouse_click, meme);
	mlx_hook(meme->win_ptr, 6, 0, mouse_move, meme);
	mlx_hook(meme->win_ptr, 4, 0, mouse_press, meme);
	mlx_hook(meme->win_ptr, 5, 0, mouse_release, meme);

	mlx_hook(meme->win_ptr, 2, 0, key_press1, meme); //debug key_press
    mlx_hook(meme->win_ptr, 3, 0, key_release1, meme);

	mlx_loop(meme->mlx_ptr);
	return (0);
	//[mlx_hook 2nd param][6-mousemove][5-buttonrelease][4-buttonpress]
	//[3-keyrelease][2-keypress][1-undef][0-undef]
	//mlx_hook 3rd param-??
}

void	blackout(t_window *meme)
{
	int	i;
	int	j;

	j = 0;
	while (j < WINY)
	{
		i = -1;
		while (++i < WINX)
		{
			mlx_pixel_put(meme->mlx_ptr, meme->win_ptr, i, j, 0x000000); //black
		}
		j++;
	}
}
/*
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
*/
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
            trianglebuf((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
                     (t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)},
                     (t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j, 1)}, meme, map);
            //triangle2((t_point){.x = i + 1, .y = j + 1, .color = pp(map, i, j, 1)}, //TODO fix dis
                 //    (t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)},
                  //   (t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j, 1)}, meme, map);
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