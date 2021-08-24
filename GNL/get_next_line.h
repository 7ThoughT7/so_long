/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmohamme <bmohamme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:58:35 by bmohamme          #+#    #+#             */
/*   Updated: 2021/08/24 18:58:35 by bmohamme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 10

char	*ft_strdup(char *s);
size_t	ft_strlen(char *c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int		get_next_line(int fd, char **line);

#endif
