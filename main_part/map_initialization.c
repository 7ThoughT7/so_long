/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:52:41 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/23 18:54:25 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	read_maps(char **argv, t_game *game)
{
	int		i;
	int		fd;
	int		gnl;
	char	*line;

	i = 0;
	gnl = 1;
	file_extension_check(argv);
	str_num(game, argv);
	game->info.map = (char **) malloc(sizeof(char *)
			* (game->info.str_num + 2));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_game(1);
	while (gnl)
	{
		gnl = get_next_line(fd, &line);
		game->info.map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	if (gnl == -1)
		exit_game(1);
	game->info.map[i] = NULL;
}

void	position(t_game *game)
{
	int	y;
	int	x;

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
}

void	image(t_game *game)
{
	game->pictures.wall = mlx_xpm_file_to_image(game->info.mlx, \
	"image/wall.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.player = mlx_xpm_file_to_image(game->info.mlx, \
	"image/spider_3.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.player_a = mlx_xpm_file_to_image(game->info.mlx, \
	"image/spider_2.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.player_s = mlx_xpm_file_to_image(game->info.mlx, \
	"image/spider_0.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.player_d = mlx_xpm_file_to_image(game->info.mlx, \
	"image/spider_1.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.coins = mlx_xpm_file_to_image(game->info.mlx, \
	"image/fly.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.web = mlx_xpm_file_to_image(game->info.mlx, \
	"image/web.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.exit_0 = mlx_xpm_file_to_image(game->info.mlx, \
	"image/exit_0.xpm", &game->info.map_width, &game->info.map_height);
	game->pictures.exit_1 = mlx_xpm_file_to_image(game->info.mlx, \
	"image/exit_1.xpm", &game->info.map_width, &game->info.map_height);
}

static void	filling_1PC0(t_game *game, int y, int x)
{
	if (game->info.map[y][x] == '1')
		mlx_put_image_to_window(game->info.mlx, game->info.win, \
		game->pictures.wall, x * 50, y * 50);
	if (game->info.map[y][x] == 'P')
		mlx_put_image_to_window(game->info.mlx, game->info.win, \
		game->pictures.player, x * 50, y * 50);
	if (game->info.map[y][x] == 'C')
		mlx_put_image_to_window(game->info.mlx, game->info.win, \
		game->pictures.coins, x * 50, y * 50);
	if (game->info.map[y][x] == '0')
		mlx_put_image_to_window(game->info.mlx, game->info.win, \
		game->pictures.web, x * 50, y * 50);
}

void	filling_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[y][x] == '1' || game->info.map[y][x] == 'P'
			|| game->info.map[y][x] == 'C' || game->info.map[y][x] == '0')
				filling_1PC0(game, y, x);
			if (game->info.map[y][x] == 'E')
				mlx_put_image_to_window(game->info.mlx, game->info.win, \
				game->pictures.exit_0, x * 50, y * 50);
			x++;
		}
		y++;
	}
}
