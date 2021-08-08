#include "so_long.h"

void	len_map(t_game *game, char **argv)
{
	int fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	game->param.len_map = 2;
	while (get_next_line(fd, &line))
	{
		game->param.len_map++;
		free(line);
	}
	free(line);
}

void	read_maps(char **argv, t_game *game)
{
	int		i;
	int		fd;
	int		gnl;
	char	*line;

	i = 0;
	gnl = 1;
	len_map(game, argv);
	game->param.map = (char **) malloc(sizeof(char *) * (game->param.len_map  + 2));
	fd = open(argv[1], O_RDONLY);
	while (gnl)
	{
		gnl = get_next_line(fd, &line);
		game->param.map[i++] = ft_strdup(line);
		free(line);
	}
	game->param.map[i] = NULL;
//	free(line);
}

void	position(t_game *game)
{
	int y;
	int x;

	y = 0;
	game->param.coins_num = 0;
	while (game->param.map[y])
	{
		x = 0;
		while (game->param.map[y][x])
		{
			if (game->param.map[y][x] == 'P')
			{
				game->param.p_x = x;
				game->param.p_y = y;
			}
			if (game->param.map[y][x] == 'C')
				game->param.coins_num++;
			x++;
		}
		y++;
	}
	game->param.map_width = x * 50;
	game->param.map_height = y * 50;
}

void	image(t_game *game)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	game->pictures.wall = mlx_xpm_file_to_image(game->param.mlx,
										"image/wall.xpm", &x, &y);
	game->pictures.player = mlx_xpm_file_to_image(game->param.mlx,
										 "image/spider_0.xpm", &x, &y);
	game->pictures.coins = mlx_xpm_file_to_image(game->param.mlx,
										 "image/fly.xpm", &x, &y);
	game->pictures.web = mlx_xpm_file_to_image(game->param.mlx,
										"image/aa.xpm", &x, &y);
	game->pictures.exit1 = mlx_xpm_file_to_image(game->param.mlx,
									  "image/exit2.xpm", &x, &y);
}

void	filling_map(t_game *game)
{
	int x;
	int	y;

	y = 0;
	while (game->param.map[y])
	{
		x = 0;
		while (game->param.map[y][x])
		{
			if (game->param.map[y][x] == '1')
				mlx_put_image_to_window(game->param.mlx, game->param.win,
										game->pictures.wall,
										x * 50, y * 50);
			if (game->param.map[y][x] == 'P')
				mlx_put_image_to_window(game->param.mlx, game->param.win,
										game->pictures.player, x * 50, y * 50);
			if (game->param.map[y][x] == 'C')
				mlx_put_image_to_window(game->param.mlx, game->param.win,
										game->pictures.coins, x * 50, y * 50);
			if (game->param.map[y][x] == '0')
				mlx_put_image_to_window(game->param.mlx, game->param.win,
										game->pictures.web,
										x * 50, y * 50);
			if (game->param.map[y][x] == 'E')
				mlx_put_image_to_window(game->param.mlx, game->param.win,
										game->pictures.exit1, x * 50, y * 50);
			x++;
		}
		y++;
	}
}

//int	key_hook(int keycode, t_game *game)
//{
//	if (keycode )
//}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	read_maps(argv, &game);
	position(&game);

	game.param.mlx = mlx_init();
	game.param.win = mlx_new_window(game.param.mlx, game.param.map_width, game.param.map_height,
							  "So_long!");
	image(&game);
	filling_map(&game);
//	mlx_hook(game.param.mlx, 2, (1L << 0), key_hook, &game);
	mlx_loop(game.param.mlx);
}