#include "so_long.h"

void	len_map(t_game *game, char **argv)
{
	int fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	game->info.len_map = 1;
	while (get_next_line(fd, &line))
	{
		game->info.len_map++;
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
	game->info.map = (char **) malloc(sizeof(char *) * (game->info.len_map
			+ 2));
	fd = open(argv[1], O_RDONLY);
	while (gnl)
	{
		gnl = get_next_line(fd, &line);
		game->info.map[i] = ft_strdup(line);
		printf("%s\n", game->info.map[i]);
		i++;
		free(line);
	}
	game->info.map[i] = NULL;
//	free(line);
}

void	position(t_game *game)
{
	int y;
	int x;

	y = 0;
	game->info.coins_num = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[y][x] == 'P')
			{
				game->info.p_y = y;
				game->info.p_x = x;
			}
			if (game->info.map[y][x] == 'C')
				game->info.coins_num++;
			x++;
		}
		y++;
	}
	game->info.map_width = x * 50;
	game->info.map_height = y * 50;
	printf("width: %d\nheight: %d\nx: %d\ny: %d\n coins: %d\n", game->info
	.map_width, game->info.map_height, x, y, game->info.coins_num);
}

void	image(t_game *game)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	game->pictures.wall = mlx_xpm_file_to_image(game->info.mlx,
										"image/wall.xpm", &game->info
										.map_width, &game->info.map_height);
	game->pictures.player = mlx_xpm_file_to_image(game->info.mlx,
										 "image/spider_0.xpm", &game->info
					.map_width, &game->info.map_height);
	game->pictures.coins = mlx_xpm_file_to_image(game->info.mlx,
										 "image/fly.xpm", &game->info
					.map_width, &game->info.map_height);
	game->pictures.web = mlx_xpm_file_to_image(game->info.mlx,
										"image/web.xpm", &game->info
					.map_width, &game->info.map_height);
	game->pictures.exit_0 = mlx_xpm_file_to_image(game->info.mlx,
									  "image/exit_0.xpm", &game->info
					.map_width, &game->info.map_height);
}

void	filling_map(t_game *game)
{
	int x;
	int	y;

	y = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[y][x] == '1')
				mlx_put_image_to_window(game->info.mlx, game->info.win,
										game->pictures.wall,
										x * 50, y * 50);
			if (game->info.map[y][x] == 'P')
				mlx_put_image_to_window(game->info.mlx, game->info.win,
										game->pictures.player, x * 50, y * 50);
			if (game->info.map[y][x] == 'C')
				mlx_put_image_to_window(game->info.mlx, game->info.win,
										game->pictures.coins, x * 50, y * 50);
			if (game->info.map[y][x] == '0')
				mlx_put_image_to_window(game->info.mlx, game->info.win,
										game->pictures.web, x * 50, y * 50);
			if (game->info.map[y][x] == 'E')
				mlx_put_image_to_window(game->info.mlx, game->info.win,
										game->pictures.exit_0, x * 50, y * 50);
			x++;
		}
		y++;
	}
}

void	button_handling(t_game *game, int x, int y)
{
	printf("x = %d\ny = %d\n", x, y);


	if (game->info.map[game->info.p_x + x][game->info.p_y + y] == '1')
		return;
	else //if (game->info.map[game->info.p_x + x][game->info.p_y + y] != '1')
	{

//		printf("befor game->info.coins_num = %d\n", game->info.coins_num);

		if (game->info.map[game->info.p_y + y][game->info.p_x + x] == 'E' &&
		game->info.coins_num == 0)
			exit(0);	/** почистить мапу */
		else if (game->info.map[game->info.p_y + y][game->info.p_x + x] == '0')
		{
			game->info.map[game->info.p_y + y][game->info.p_x + x] = 'P';
			mlx_put_image_to_window(game->info.mlx, game->info.win,
			game->pictures.player, (game->info.p_x + x) * 50, (game->info.p_y + y) * 50);
			game->info.map[game->info.p_y][game->info.p_x] = '0';
			mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures
			.web, game->info.p_x * 50, game->info.p_y * 50);
			game->info.p_x += x;
			game->info.p_y += y;
			game->info.step++;
		}
		else if (game->info.map[game->info.p_y + y][game->info.p_x + x] == 'C')
		{
			game->info.map[game->info.p_y + y][game->info.p_x + x] = 'P';
			mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures
					.player, (game->info.p_x + x) * 50, (game->info.p_y + y) * 50);
			game->info.map[game->info.p_y][game->info.p_x] = '0';
			mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures
					.web, game->info.p_x * 50, game->info.p_y * 50);
			game->info.p_x += x;
			game->info.p_y += y;
			game->info.step++;
			game->info.coins_num--;
		}

		int a = 0;
		while (game->info.map[a])
		{
			int b = 0;
			while (game->info.map[a][b])
			{
				printf("%c", game->info.map[a][b]);
				b++;
			}
			printf("%c", '\n');
			a++;
		}

//		printf("after game->info.coins_num = %d\n", game->info.coins_num);
	}
}



//void	handling_0(t_game *game, int x, int y)
//{
//	game->info.map[game->info.p_x + x][game->info.p_y + y] = 'P';
//	mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures
//	.player, (game->info.p_x + x) * 50, (game->info.p_y + y) * 50);
//	game->info.map[game->info.p_x][game->info.p_y] = '0';
//	mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures
//	.web, game->info.p_x * 50, game->info.p_y * 50);
//	game->info.p_x += x;
//	game->info.p_y += y;
//	game->info.step++;
//
//}
//
//
//void	button_handling(t_game *game, int x, int y)
//{
//
//	if (game->info.map[game->info.p_x + x][game->info.p_y + y] != '1')
//	{
//		if (game->info.map[game->info.p_x + x][game->info.p_y + y] == 'E' &&
//		game->info.coins_num == 0)
//			exit(0);	/** почистить мапу */
//		else if (game->info.map[game->info.p_x + x][game->info.p_y + y] == '0')
//			handling_0(game, x, y);
////		if (game->info.map[game->info.p_x + x][game->info.p_y + y] == '1')
////			return;
//		else if (game->info.map[game->info.p_x + x][game->info.p_y + y] ==
//		'C')
//		{
//			handling_0(game, x, y);
//			game->info.coins_num--;
//		}
//	}

//	int i = game->info.map_width / 50;
//	int j = game->info.map_height / 50;
//	int a = 0;
//	int b = 0;
//	while (a < i)
//	{
//		b = 0;
//		while (b < j)
//		{
//			printf("%c", game->info.map[a][b]);
//			b++;
//		}
//		a++;
//	}
//}

int	key_hook(int keycode, t_game *game)
{

//	printf("%d\n%d\n", game->info.p_x, game->info.p_y);
//	printf("%d\n%d\n", game->info.p_x, game->info.p_y);
	if (keycode == 53)
		exit(0); /** почистить мапу */
	else if (keycode == 13)
		button_handling(game, 0, -1);
	else if (keycode == 0)
		button_handling(game, -1, 0);
	else if (keycode == 1)
		button_handling(game, 0, 1);
	else if (keycode == 2)
		button_handling(game, 1, 0);
//	printf("%d\n", game->info.step);
//	filling_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	game.info.step = 0;
	read_maps(argv, &game);
	position(&game);

	game.info.mlx = mlx_init();
	game.info.win = mlx_new_window(game.info.mlx, game.info.map_width,
									game.info.map_height, "So_long!");
	image(&game);
	filling_map(&game);
//	mlx_hook(game.info.win, 17, 0, key_close, &game);
	mlx_key_hook(game.info.win, key_hook, &game);
	mlx_loop(game.info.mlx);
}