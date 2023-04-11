/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkandiyi <rkandiyi@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:03:59 by rkandiyi          #+#    #+#             */
/*   Updated: 2023/01/19 23:25:03 by rkandiyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_line(char *s, int fd)
{
	char	*buffer;
	int		b;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!s)
		s = ft_strdup("");
	b = 1;
	while (b != 0)
	{
		b = read(fd, buffer, BUFFER_SIZE);
		if (b == -1)
			return (free(s), free(buffer), NULL);
		buffer[b] = 0;
		if (b == 0)
			break ;
		s = ft_strjoin(s, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	return (s);
}

char	*get_line(char *s)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!s || !s[0])
		return (NULL);
	while (s[i] && (s[i] != '\n'))
		i++;
	line = ft_substr(s, (i + 1));
	return (line);
}

static char	*trim_firstline(char *s)
{
	char	*trim;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] != '\n'))
		i++;
	if (s[i] == '\0')
		return (free(s), NULL);
	if (s[i] == '\n')
		i++;
	trim = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!trim)
		return (NULL);
	while (s[i])
		trim[j++] = s[i++];
	trim[j] = 0;
	return (free(s), trim);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*line;

	if (BUFFER_SIZE < 0 || fd < 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	s[fd] = read_line(s[fd], fd);
	if (!s[fd])
		return (NULL);
	line = get_line(s[fd]);
	s[fd] = trim_firstline(s[fd]);
	return (line);
}
