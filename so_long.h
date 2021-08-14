#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibX/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include "GNL/get_next_line.h"

typedef struct s_info
{
	int		str_num;
	int		str_len;
	int		coins_num;
	int		step;
	char	**map;
	void	*mlx;
	void	*win;
	int		p_x;
	int		p_y;
	int		P;
	int		C;
	int		E;
	int		map_height;
	int		map_width;
}			t_info;

typedef struct s_pictures
{
	void	*wall;
	void	*player;
	void	*player_a;
	void	*player_s;
	void	*player_d;
	void	*coins;
	void	*web;
	void	*exit_0;
	void	*exit_1;
	void	*mantis;

}			t_pictures;

typedef struct s_game
{
	t_info		info;
	t_pictures	pictures;
}				t_game;

char	*str_chr(const char *s, char c);
void	str_num(t_game *game, char **argv);
int		str_len(t_game *game);
int		exit_game(int i);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	file_extension_check(char **argv);
void	read_maps(char **argv, t_game *game);
void	position(t_game *game);
void	image(t_game *game);
void	filling_map(t_game *game);

void	handling_0(t_game *game, int x, int y);
void	button_handling(t_game *game, int x, int y);
int		key_hook(int keycode, t_game *game);
void	parser(t_game *game);
void	print_step(t_game *game);
void	open_door(t_game *game);

#endif