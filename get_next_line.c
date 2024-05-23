/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:22:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/23 15:39:25 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*result;
	static char	*cache;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!cache)
		cache = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!cache)
		return (NULL);
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (call_funcs(fd, result, &cache));
}

char	*call_funcs(int fd, char *result, char **cache)
{
	char	*temp;

	if (!(*cache[0]))
	{
		*cache = reads_new_line(fd);
		if (!(*cache[0]))
			return (NULL);
	}
	while ((*cache)[0])
	{
		temp = ft_strdup(*cache);
		if (!temp)
			return (NULL);
		result = ft_strjoin(result, handle_cache(temp));
		free(temp);
		if (!result)
			return (NULL);
		if (have_new_line(*cache))
		{
			*cache = ft_strrchr(*cache, '\n', 0);
			return (result);
		}
		*cache = reads_new_line(fd);
		if (!(*cache))
		{
			break ;
			free(cache);
		}
	}
	return (result);
}

char	*handle_cache(char *cache)
{
	char	*result;

	while (have_new_line(cache))
	{
		if (have_new_line(cache) == 1)
		{
			cache = ft_strrchr(cache, '\n', 1);
			cache = ft_strjoin(cache, "\n\0");
			break ;
		}
		cache = ft_strrchr(cache, '\n', 1);
	}
	result = ft_strdup(cache);
	if (!result)
		return (NULL);
	return (result);
}

char	*reads_new_line(int fd)
{
	int		char_read;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	char_read = read(fd, buf, BUFFER_SIZE);
	if (char_read <= 0)
	{
		free(buf);		
		return (NULL);
	}
	buf[char_read] = '\0';
	return (buf);
}

int	have_new_line(char *buf)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int	main(void)
{
	int	fd;
	int	i;
	char	*line;

	i = 0;
	fd = open("./example2.txt", O_RDONLY);
	while (i++ < 4)
	{
		line = get_next_line(fd);
		printf("line [%02d]: %s", i, line);
		free(line);
	}
	close(fd);
}
