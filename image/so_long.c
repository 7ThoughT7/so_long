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

//void	key_w(t_game *game)
//{
////	exit(1);
//	if (game->param.map[game->param.p_y - 1][game->param.p_x] == '1')
//		return;
//	if (game->param.map[game->param.p_y - 1][game->param.p_x] == '0')
//	{
//		game->param.map[game->param.p_y - 1][game->param.p_x] = 'P';
//		game->param.map[game->param.p_y][game->param.p_x] = '0';
//		game->param.p_y -= 1;
//		game->pictures.player = game->pictures.player;
//	}
//	if (game->param.map[game->param.p_y - 1][game->param.p_x] == 'E')
//		exit(0);
//}

void	handling_0(t_game *game, int x, int y)
{
	game->param.map[game->param.p_x + x][game->param.p_y + y] = 'P';
	mlx_put_image_to_window(game->param.mlx, game->param.win, game->pictures
	.player, (game->param.p_x + x) * 50, (game->param.p_y + y) * 50);
	game->param.map[game->param.p_x][game->param.p_y] = '0';
	mlx_put_image_to_window(game->param.mlx, game->param.win, game->pictures
	.web, game->param.p_x * 50, game->param.p_y * 50);
	game->param.p_x += x;
	game->param.p_y += y;
	game->param.step++;
}


void	button_handling(t_game *game, int x, int y)
{

	if (game->param.map[game->param.p_x + x][game->param.p_y + y] != '1')
	{
		if (game->param.map[game->param.p_x + x][game->param.p_y + y] == '0')
			handling_0(game, x, y);
//		if (game->param.map[game->param.p_x + x][game->param.p_y + y] == '1')
//			return;
		if (game->param.map[game->param.p_x + x][game->param.p_y + y] == 'C')
		{
			handling_0(game, x, y);
			game->param.coins_num--;
		}

	}
}

int	key_hook(int keycode, t_game *game)
{

//	printf("%d\n%d\n", game->param.p_x, game->param.p_y);
//	printf("%d\n%d\n", game->param.p_x, game->param.p_y);
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
//	printf("%d\n", game->param.step);
//	filling_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	game.param.step = 0;
	read_maps(argv, &game);
	position(&game);

	game.param.mlx = mlx_init();
	game.param.win = mlx_new_window(game.param.mlx, game.param.map_width,
									game.param.map_height, "So_long!");
	image(&game);
	filling_map(&game);
//	mlx_hook(game.param.win, 17, 0, key_close, &game);
	mlx_key_hook(game.param.win, key_hook, &game);
	mlx_loop(game.param.mlx);
}