#ifndef SO_LONG_H
# define SO_LONG_H

#include "minilibX/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include "GNL/get_next_line.h"


typedef struct	s_param
{
	int		len_map;
	int 	coins_num;
	int		step;
	char	**map;
	void	*mlx;
	void	*win;
	int		p_x;
	int		p_y;
	int 	map_height;
	int 	map_width;
}				t_param;

typedef struct	s_pictures
{
	void	*wall;
	void	*player;
	void	*coins;
	void	*web;
	void	*exit1;

}			t_pictures;

typedef struct s_game
{
	t_param		param;
	t_pictures	pictures;
}				t_game;

#endif