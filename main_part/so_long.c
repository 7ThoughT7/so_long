/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:55:20 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/23 18:55:20 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_game(1);
	game.info.step = 0;
	read_maps(argv, &game);
	parser(&game);
	position(&game);
	game.info.mlx = mlx_init();
	game.info.win = mlx_new_window(game.info.mlx, game.info.map_width, \
	   game.info.map_height, "So_long!");
	image(&game);
	filling_map(&game);
	mlx_key_hook(game.info.win, key_hook, &game);
	mlx_hook(game.info.win, 17, 0, exit_game, &game);
	mlx_loop(game.info.mlx);
}
