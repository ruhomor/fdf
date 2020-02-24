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

int	main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;
	int	i;
	int	j;

	meme = (t_window*)malloc(sizeof(*meme));
	i = 0;
	j = 0;
	argc--;
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	//readmap(map, "test1");
	readmap(map, argv[1]);
	
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			printf("%d ", map->cell[i][j++]);
		printf("\n");
		i++;
	}
	
	//maperror(map); //mem debug
	meme->mlx_ptr = mlx_init();
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, 1000, 1000, "MEME");
	meme->zoom = 20;
	drawmap(meme, map);
	mlx_key_hook(meme->win_ptr, deal_key, NULL);
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
			drawline((t_point){.x = i, .y = j},
					(t_point){.x = i + 1, .y = j}, meme, map);
			drawline((t_point){.x = i, .y = j},
					(t_point){.x = i, .y = j + 1}, meme, map);
			i++;
		}
		j++;
	}
	j = map->height - 1; // 1 1 1
	i = -1;		     // 1 1 1 //
	while (++i < map->width - 1)
		drawline((t_point){.x = i, .y = j},
				(t_point){.x = i + 1, .y = j}, meme, map);
	i = map->width - 1;
	j = -1;
	while (++j < map->height - 1)
		drawline((t_point){.x = i, .y = j},
				(t_point){.x = i, .y = j + 1}, meme, map);
}
