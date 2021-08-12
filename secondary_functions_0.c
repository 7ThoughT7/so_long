#include "so_long.h"

void	str_num(t_game *game, char **argv)
{
	int fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_game(1);
	game->info.str_num = 1;
	while (get_next_line(fd, &line))
	{
		game->info.str_num++;
		free(line);
	}
	free(line);
}

int	str_len(t_game *game)
{
	int	x;

	x = 0;
	game->info.str_len = 0;
	while (game->info.map[0][x])
	{
		game->info.str_len++;
		x++;
	}
	return (game->info.str_len);
}

char	*str_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

void	exit_game(int i)
{
	if (i == 1)
		printf("%s", "INVALID MAP");
	if (i == 2)
		printf("%s", "YOU WIN");
	if (i == 3)
		printf("%s", "GAME OVER");
	exit(1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}