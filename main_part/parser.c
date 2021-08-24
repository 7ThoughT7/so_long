/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:56:04 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/24 17:18:23 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

static void	checking_walls(t_game *game)
{
	int		y;
	int		x;
	char	*str;
	int		last_y;
	int		last_x;

	y = 0;
	str = "10PEC";
	last_y = game->info.str_num - 1;
	last_x = (str_len(game) - 1);
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[0][x] != '1' || game->info.map[y][0] != '1' || \
			game->info.map[y][last_x] != '1' || \
			game->info.map[last_y][x] != '1' || \
			!str_chr(str, game->info.map[y][x]))
				exit_game(1);
			x++;
		}
		y++;
	}
}

static void	check_str_len(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
			x++;
		if (game->info.str_len != x)
			exit_game(1);
		y++;
	}
	if (x > 58 || y > 32)
		exit_game(1);
}

void	file_extension_check(char **argv)
{
	int		fd;
	char	*dot;
	char	*ber;

	ber = ".ber";
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		exit_game(1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_game(1);
	dot = ft_strchr(argv[1], '.');
	if (dot[0] == '\0')
		exit_game(1);
	if (ft_strncmp(dot, ber, 4) != 0)
		exit_game(1);
}

void	check_amount_element(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	game->info.P = 0;
	game->info.C = 0;
	game->info.E = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[y][x] == 'P')
				game->info.P++;
			if (game->info.map[y][x] == 'C')
				game->info.C++;
			if (game->info.map[y][x] == 'E')
				game->info.E++;
			x++;
		}
		y++;
	}
	if (game->info.P != 1 || game->info.C < 1 || game->info.E < 1)
		exit_game(1);
}

void	parser(t_game *game)
{
	checking_walls(game);
	check_str_len(game);
	check_amount_element(game);
}
