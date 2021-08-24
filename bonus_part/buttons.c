/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:55:41 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/23 18:55:41 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	handling_0(t_game *game, int x, int y)
{
	game->info.map[game->info.p_y + y][game->info.p_x + x] = 'P';
	if (x == 0 && y == -1)
		mlx_put_image_to_window(game->info.mlx, game->info.win,
			game->pictures.player, (game->info.p_x + x) * 50,
			(game->info.p_y + y) * 50);
	if (x == -1 && y == 0)
		mlx_put_image_to_window(game->info.mlx, game->info.win,
			game->pictures.player_a, (game->info.p_x + x) * 50,
			(game->info.p_y + y) * 50);
	if (x == 0 && y == 1)
		mlx_put_image_to_window(game->info.mlx, game->info.win,
			game->pictures.player_s, (game->info.p_x + x) * 50,
			(game->info.p_y + y) * 50);
	if (x == 1 && y == 0)
		mlx_put_image_to_window(game->info.mlx, game->info.win,
			game->pictures.player_d, (game->info.p_x + x) * 50,
			(game->info.p_y + y) * 50);
	game->info.map[game->info.p_y][game->info.p_x] = '0';
	mlx_put_image_to_window(game->info.mlx, game->info.win, game->pictures.web,
		game->info.p_x * 50, game->info.p_y * 50);
	game->info.p_x += x;
	game->info.p_y += y;
	game->info.step++;
	print_step(game);
}

void	button_handling(t_game *game, int x, int y)
{
	if (game->info.map[game->info.p_y + y][game->info.p_x + x] != '1')
	{
		if (game->info.map[game->info.p_y + y][game->info.p_x + x] == 'E' &&
		game->info.coins_num == 0)
			exit_game(2);
		else if (game->info.map[game->info.p_y + y][game->info.p_x + x] == '0')
			handling_0(game, x, y);
		else if (game->info.map[game->info.p_y + y][game->info.p_x + x] == 'C')
		{
			handling_0(game, x, y);
			game->info.coins_num--;
			if (game->info.coins_num == 0)
				open_door(game);
		}
		else if (game->info.map[game->info.p_y + y][game->info.p_x + x] == 'M')
			exit_game(3);
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 53)
		exit_game(0);
	else if (keycode == 13)
		button_handling(game, 0, -1);
	else if (keycode == 0)
		button_handling(game, -1, 0);
	else if (keycode == 1)
		button_handling(game, 0, 1);
	else if (keycode == 2)
		button_handling(game, 1, 0);
	return (0);
}
