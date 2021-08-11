#include "so_long.h"

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
	game.info.win = mlx_new_window(game.info.mlx, game.info.map_width,
									game.info.map_height, "So_long!");
	image(&game);
	filling_map(&game);
//	mlx_hook(game.info.win, 17, 0, key_close, &game);
	mlx_key_hook(game.info.win, key_hook, &game);
	mlx_loop(game.info.mlx);
}