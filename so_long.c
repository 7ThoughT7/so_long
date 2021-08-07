#include "so_long.h"

void	len_map(t_data *vars, char **argv)
{
	int fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	vars->len_map = 2;
	while (get_next_line(fd, &line))
	{
		vars->len_map++;
		free(line);
	}
	free(line);
}

void	read_maps(char **argv, t_data *vars)
{
	int		i;
	int		fd;
	int		gnl;
	char	*line;

	i = 0;
	gnl = 1;
	len_map(vars, argv);
	vars->map = (char **) malloc(sizeof(char *) * (vars->len_map  + 2));
	fd = open(argv[1], O_RDONLY);
	while (gnl)
	{
		gnl = get_next_line(fd, &line);
		vars->map[i++] = ft_strdup(line);
		free(line);
	}
	vars->map[i] = NULL;
//	free(line);
}

void	position(t_data *vars)
{
	int y;
	int x;

	y = 0;
	vars->coins = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (vars->map[y][x] == 'P')
			{
				vars->p_x = x;
				vars->p_y = y;
			}
			if (vars->map[y][x] == 'C')
				vars->coins++;
			x++;
		}
		y++;
	}
	vars->map_width = x * 50;
	vars->map_height = y * 50;
}

void	image(t_data *vars)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	vars->wall = mlx_xpm_file_to_image(vars->mlx,
										"image/wall.xpm", &x, &y);
	vars->player = mlx_xpm_file_to_image(vars->mlx,
										 "image/spider_0.xpm", &x, &y);
	vars->coins = mlx_xpm_file_to_image(vars->mlx,
										 "image/fly.xpm", &x, &y);
	vars->web = mlx_xpm_file_to_image(vars->mlx,
										"image/aa.xpm", &x, &y);
	vars->exit1 = mlx_xpm_file_to_image(vars->mlx,
									  "image/exit2.xpm", &x, &y);
}

void	filling_map(t_data *vars)
{
	int x;
	int	y;

	y = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
		{
			if (vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall, x
				* 50, y * 50);
			if (vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->player, x
				* 50, y * 50);
			if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->coins, x
				* 50, y * 50);
			if (vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->web, x *
				50, y * 50);
			if (vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->exit1, x
				* 50, y * 50);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_data 	vars;

	if (argc != 2)
		return (1);
	read_maps(argv, &vars);
	position(&vars);

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_width, vars.map_height,
							  "So_long!");
	image(&vars);
	filling_map(&vars);

	mlx_loop(vars.mlx);
}