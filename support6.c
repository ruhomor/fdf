#include "fdf.h"

int					main(int argc, char **argv)
{
	t_map		*map;
	t_window	*meme;

	meme = initwindow();
	if (argc != 2)
	{
		ft_putstr_fd("fdf: wrond number of arguments\n", 2);
		maperror(NULL, meme);
	}
	map = (t_map*)malloc(sizeof(*map));
	map->cell = NULL;
	readmap(map, argv[1], meme);
	memerememe(map, meme);
	return (0);
}

void				liner(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				 (t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
														   j, 1)}, meme);
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				 (t_point){.x = i, .y = j + 1, .color = pp(map, i,
														   j + 1, 1)}, meme);
	if (renmode == 2)
		drawlinecool(
				(t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
														  j, 1)}, meme);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
					 (t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1, 1)},
					 meme);
}

void				liner1(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				 (t_point){.x = i + 1, .y = j, .color = pp(map, i + 1, j,
														   1)}, meme);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
					 (t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
															   j, 1)}, meme);
}

void				liner2(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode != 2)
		drawline((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				 (t_point){.x = i, .y = j + 1, .color = pp(map, i, j + 1,
														   1)}, meme);
	if (renmode == 2)
		drawlinecool((t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
					 (t_point){.x = i, .y = j + 1, .color = pp(map, i,
															   j + 1, 1)}, meme);
}

void				triangle(t_window *meme, int renmode, int i, int j)
{
	t_map *map;

	map = meme->map;
	if (renmode >= 3)
		trianglebuf(
				(t_point){.x = i, .y = j, .color = pp(map, i, j, 1)},
				(t_point){.x = i, .y = j + 1, .color = pp(map, i,
														  j + 1, 1)},
				(t_point){.x = i + 1, .y = j, .color = pp(map, i + 1,
														  j, 1)}, meme);
	if (renmode >= 4)
		trianglebuf((t_point){.x = i + 1, .y = j + 1, .color = pp(map,
																  i + 1, j + 1, 1)},
					(t_point){.x = i, .y = j + 1, .color = pp(map, i,
															  j + 1, 1)},
					(t_point){.x = i + 1, .y = j, .color = pp(map,
															  i + 1, j, 1)}, meme);
}
