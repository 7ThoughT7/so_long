#ifndef SO_LONG_H
# define SO_LONG_H

#include "minilibX/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include "GNL/get_next_line.h"


typedef struct	s_data
{
	int		len_map;
	char	**map;
	void	*mlx;
	void	*win;
	int		p_x;
	int		p_y;
	int 	map_height;
	int 	map_width;
	void	*wall;
	void	*player;
	void	*coins;
	void	*web;
	void	*exit1;
}				t_data;


#endif