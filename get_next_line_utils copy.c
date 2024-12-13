/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oben-jha <oben-jha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:25:20 by oben-jha          #+#    #+#             */
/*   Updated: 2024/12/12 11:40:55 by oben-jha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
		return (((char *)s) + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

static void	copy_string(char *dest, const char *src, int *index)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[*index] = src[i];
		(*index)++;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	ls1;
	size_t	ls2;
	char	*result;
	int		index;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	result = malloc((ls1 + ls2) + 1);
	if (!result)
		return (NULL);
	index = 0;
	copy_string(result, s1, &index);
	copy_string(result, s2, &index);
	result[index] = '\0';
	free(s1);
	s1 = NULL;
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	int		beg;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	beg = start;
	while (i < len && s[beg])
	{
		substr[i] = s[beg];
		i++;
		beg++;
	}
	substr[i] = '\0';
	return (substr);
}
