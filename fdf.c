#include <stdio.h>
#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;
	int	i;
	int	j;

	i = 0;
	j = 0;
	argc--;
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	//readmap(map, "test1");
	readmap(map, argv[1]);
	/*
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
			printf("%d ", map->cell[i][j++]);
		printf("\n");
		i++;
	}
	*/
	//maperror(map); //mem debug
	meme->mlx_ptr = mlx_init();
	meme->win_ptr = mlx_new_window(meme->mlx_ptr, 1000, 1000, "MEME");
	meme->zoom = 20;

	drawmap(meme, map);
	mlx_key_hook(meme->win_ptr, deal_key, NULL);
	mlx_loop(meme->mlx_ptr);
	return (0);
}

void	drawmap(t_window meme, t_map map)
{
		int	i;
		int	j;

		j = 0;
		while (j < map->height)
		{
			i = 0;
			while (i < map->width)
			{
				drawline((t_point){.x = i, .y = j}, (t_point){.x = i + 1, .y = j}, meme);
				drawline((t_point){.x = i, .y = j}, (t_point){.x = i++, .y = j + 1}, meme);
			}
			j++;
		}
}
