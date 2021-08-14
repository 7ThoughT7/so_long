#include "get_next_line.h"

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	size_t	n;

	if (!s1)
		return (ft_strdup(s2));
	n = (ft_strlen(s1) + ft_strlen(s2));
	str = (char *)malloc(n + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(char *s, int c)
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
