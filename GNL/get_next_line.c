/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:55:29 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/23 18:55:29 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static int	check_rem(char *rem)
{
	if (!rem)
		return (0);
	if ((ft_strchr(rem, '\n')))
		return (1);
	return (0);
}

static void	write_line(char **rem, char **line)
{
	char	*str_end;
	char	*tmp;

	if (*rem == NULL)
	{
		*line = "";
		return ;
	}
	str_end = ft_strchr(*rem, '\n');
	if (str_end)
	{
		tmp = *rem;
		str_end[0] = '\0';
		*line = ft_strdup(*rem);
		*rem = ft_strdup(++str_end);
		free(tmp);
	}
	else
	{
		*line = ft_strdup(*rem);
		free(*rem);
		*rem = NULL;
		return ;
	}
}

static int	read_rem(char *buf, char **rem, int fd, char **line)
{
	int		byte_r;

	byte_r = 1;
	while (byte_r && (check_rem(*rem) == 0))
	{
		byte_r = read(fd, buf, BUFFER_SIZE);
		if (byte_r < 0)
		{
			*line = NULL;
			return (-1);
		}
		buf[byte_r] = '\0';
		if (!(*rem))
		{
			*rem = ft_strdup(buf);
			if (!rem)
				return (-1);
		}
		else
			*rem = ft_strjoin(*rem, buf);
	}
	write_line(rem, line);
	if (byte_r)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*rem;
	int			bull;

	if (fd < 0 || (BUFFER_SIZE <= 0) || !line)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bull = read_rem(buf, &rem, fd, line);
	free(buf);
	return (bull);
}
