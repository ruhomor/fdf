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

#include "fdf.h"

void				linertriangle(t_window *meme, int renmode, int i, int j)
{
	liner(meme, renmode, i, j);
	triangle(meme, renmode, i, j);
}

void				drawmap(t_window *meme)
{
	int		i;
	int		j;
	int		renmode;
	t_map	*map;

	map = meme->map;
	renmode = meme->renmod;
	j = -1;
	while (++j < map->height - 1)
	{
		i = -1;
		while (++i < map->width - 1)
			linertriangle(meme, renmode, i, j);
	}
	j = map->height - 1;
	i = -1;
	while (++i < map->width - 1)
		liner1(meme, renmode, i, j);
	i = map->width - 1;
	j = -1;
	while (++j < map->height - 1)
		liner2(meme, renmode, i, j);
	initbuf(meme->zbuf, WINX * WINY);
}
