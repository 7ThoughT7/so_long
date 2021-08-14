#include "so_long.h"

static int	isnegative(int n)
{
	int		i;
	int		negative;

	i = 1;
	negative = 0;
	if (n < 0)
	{
		n *= -1;
		negative = 1;
	}
	return (negative);
}

static int	len(int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		neg;
	char	*str;
	int		i;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = isnegative(n);
	if (n < 0)
		n *= -1;
	i = len(n) + neg;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[i] = n + '0';
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n /= 10;
	}
	if (neg == 1)
		str[i] = '-';
	return (str);
}

void	print_step(t_game *game)
{
	char	*str_1;
	char	*str_0;

	mlx_put_image_to_window(game->info.mlx, game->info.win, \
	game->pictures.wall, 0 * 50, 0 * 50);
	mlx_put_image_to_window(game->info.mlx, game->info.win, \
	game->pictures.wall, 1 * 50, 0 * 50);
	str_0 = "Step: ";
	str_1 = ft_itoa(game->info.step);
	mlx_string_put(game->info.mlx, game->info.win, 12, 12, 0xFF000000,
		str_0);
	mlx_string_put(game->info.mlx, game->info.win, 62, 12, 0xFF000000,
		str_1);
	free(str_1);
}

void	open_door(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->info.map[y])
	{
		x = 0;
		while (game->info.map[y][x])
		{
			if (game->info.map[y][x] == 'E')
				mlx_put_image_to_window(game->info.mlx, game->info.win, \
				game->pictures.exit_1, x * 50, y * 50);
			x++;
		}
		y++;
	}
}
