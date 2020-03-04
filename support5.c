/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kachiote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:43:51 by kachiote          #+#    #+#             */
/*   Updated: 2020/03/04 06:43:53 by kachiote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					key_release1(int keycode, void *p)
{
	t_window *meme;

	meme = (t_window *)p;
	if (keycode == 126)
		meme->shift.u_flag = (meme->shift.u_flag == -1) ? 0 : 1;
	if (keycode == 125)
		meme->shift.d_flag = (meme->shift.d_flag == 1) ? 0 : -1;
	if (keycode == 124)
		meme->shift.r_flag = (meme->shift.r_flag == 1) ? 0 : -1;
	if (keycode == 123)
		meme->shift.l_flag = (meme->shift.l_flag == -1) ? 0 : 1;
	return (0);
}

void				initbuf(long int *arr, long int size)
{
	long int i;

	i = -1;
	while (++i < size)
		*arr++ = MAX;
}

t_window			*initwindow(void)
{
	t_window *meme;

	meme = (t_window *)malloc(sizeof(*meme));
	meme->zbuf = (long int *)malloc(
			WINY * WINX * sizeof(*(meme->zbuf)));
	initbuf(meme->zbuf, WINX * WINY);
	meme->win_ptr = NULL;
	meme->drag_flag = 0;
	meme->shift.r_flag = 0;
	meme->shift.l_flag = 0;
	meme->shift.u_flag = 0;
	meme->shift.d_flag = 0;
	meme->angle.a = 0;
	meme->angle.b = 0;
	meme->zoom = 2;
	meme->attitude = 1;
	meme->renmod = 1;
	meme->prjk = 0;
	return (meme);
}

void				hookhandler(t_window *meme)
{
	mlx_hook(meme->win_ptr, 6, 0, mouse_move, meme);
	mlx_hook(meme->win_ptr, 4, 0, mouse_press, meme);
	mlx_hook(meme->win_ptr, 5, 0, mouse_release, meme);
	mlx_hook(meme->win_ptr, 2, 0, key_press1, meme);
	mlx_hook(meme->win_ptr, 3, 0, key_release1, meme);
	mlx_loop(meme->mlx_ptr);
}

void				memerememe(t_map *map, t_window *meme)
{
	meme->shift.x = WINX / 2 - map->width / 2;
	meme->shift.y = WINY / 2 - map->height / 2;
	meme->mlx_ptr = mlx_init();
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, WINX, WINY, "MEME");
	map->colorrange = map->max - map->min;
	meme->map = map;
	drawmap(meme);
	hookhandler(meme);
}
