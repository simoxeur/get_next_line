/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtalbi <mtalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:46:37 by mtalbi            #+#    #+#             */
/*   Updated: 2024/02/01 16:42:35 by mtalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_new_collect(char *str)
{
	char	*new_str;
	int		i;
	size_t	len;

	if (!str || !*str)
		return (NULL);
	new_str = NULL;
	i = 0;
	len = ft_strlen(str, '\n') + 1;
	if (ft_check_nl(str) == 0 || str[len] == '\0')
		return (NULL);
	new_str = (char *)malloc((ft_strlen(str, '\0') - len + (size_t)1));
	if (!new_str)
		return (NULL);
	while (str[len] != '\0')
	{
		new_str[i] = str[len];
		i++;
		len++;
	}
	new_str[i] = '\0';
	if (!*new_str)
		return (free(new_str), NULL);
	return (new_str);
}

static char	*ft_get_line(int fd, char *buffer)
{
	static char	*collect[MAX_FD];
	char		*line;
	char		*tmp;
	ssize_t		readed;
	size_t		len;

	readed = 1;
	line = NULL;
	while (readed > 0 && ft_check_nl(collect[fd]) == 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
			return (free(collect[fd]), collect[fd] = NULL, NULL);
		buffer[readed] = '\0';
		collect[fd] = ft_strnjoin(collect[fd], buffer, readed);
	}
	len = ft_strlen(collect[fd], '\n') + 1;
	if (ft_check_nl(collect[fd]) == 0)
		len = ft_strlen(collect[fd], '\0');
	line = ft_strnjoin(line, collect[fd], len);
	tmp = collect[fd];
	collect[fd] = ft_new_collect(collect[fd]);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (free(buffer), NULL);
	line = ft_get_line(fd, buffer);
	free(buffer);
	if (!line || *line == '\0')
		return (free(line), NULL);
	return (line);
}
