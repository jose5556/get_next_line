/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:22:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/26 15:38:15 by joseoliv         ###   ########.fr       */
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
	{
		free(cache);
		return (NULL);
	}
	result[0] = '\0';
	return (call_funcs(fd, result, &cache));
}

char	*call_funcs(int fd, char *result, char **cache)
{
	char	*temp;
	char	*result_temp;

	if (!(*cache) || !(*cache[0]))
	{
		
		*cache = reads_new_line(fd);
		if (!(*cache))
			return (NULL);
	}
	while ((*cache)[0])
	{
		temp = ft_strdup(*cache);
		if (!temp)
		{
			free(result);	
			return (NULL);
		}
		result_temp = ft_strjoin(result, handle_cache(temp));
		free(temp);
		if (!result_temp)
		{
			free (result);
			return (NULL);
		}
		free(result);
		result = result_temp;
		if (have_new_line(*cache))
		{
			*cache = ft_strrchr(*cache, '\n', 0);
			return (result);
		}
		*cache = reads_new_line(fd);
		if (!(*cache))
			break ;
	}
	return (result);
}

char	*handle_cache(char *cache)
{
	char	*result;
	char	*temp;
	char	*new_cache;

	while (have_new_line(cache))
	{
		if (have_new_line(cache) == 1)
		{
			temp = ft_strrchr(cache, '\n', 1);
			if (temp)
			{
				new_cache = ft_strjoin(temp, "\n\0");
				free(cache);
				cache = new_cache;
				break ;
			}
		}
		temp = ft_strrchr(cache, '\n', 1);
		if (temp)
			cache = temp;
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
	while (i++ < 3)
	{
		line = get_next_line(fd);
		printf("line %d %s", i, line);
		free(line);
	}
	close(fd);
}
