/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:47:03 by oben-jha          #+#    #+#             */
/*   Updated: 2024/12/12 21:39:18 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

static char	*get_line(char *reserve)
{
	int		start;
	char	*line;
	int		i;

	start = 0;
	i = 0;
	while (reserve[i] != '\n' && reserve[i] != '\0')
		i++;
	if (reserve[i] == '\n')
		i++;
	line = ft_substr(reserve, start, i);
	return (line);
}

static char	*update_reserve(char *reserve)
{
	char	*new_res;
	int		i;

	i = 0;
	while (reserve[i] != '\n' && reserve[i] != '\0')
		i++;
	new_res = ft_substr(reserve, i + 1, ft_strlen(reserve) - i - 1);
	free(reserve);
	reserve = NULL;
	return (new_res);
}

static char	*helper_func(char *buffer, char *reserve, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, (size_t)BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		reserve = ft_strjoin(reserve, buffer);
		if (!reserve)
			return (NULL);
		if (ft_strchr(reserve, '\n'))
			break ;
		bytes_read = read(fd, buffer, (size_t)BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read == -1)
		return (free(reserve), reserve = NULL, NULL);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc((size_t) BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	reserve = helper_func(buffer, reserve, fd);
	if (!reserve || *reserve == '\0')
		return (free(reserve), reserve = NULL, NULL);
	line = get_line(reserve);
	reserve = update_reserve(reserve);
	return (line);
}
// #include <libc.h>

// int main(void)
// {
// 	int fd = open("test.txt", O_RDWR);

// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
	
// 	return 0;
// }