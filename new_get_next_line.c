/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_next_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:22:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/20 21:59:25 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_get_next_line(int fd)
{
	static char	*cache;
	char		*result;
	int			first_time;
	char		*temp;

	first_time = 1;
	result = NULL;
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
	while (cache[0] || first_time)
	{
		first_time = 0;
		cache = reads_new_line(fd);
		temp = ft_strdup(cache);
		result = ft_strjoin(result, handle_cache(temp));
		free(temp);
		if (have_new_line(cache))
		{
			cache = ft_strrchr(cache, '\n', 0);		
			return (result);
		}
	}
	return (result);
}

char	*handle_new_line(char *append_result)
{
	while (have_new_line(append_result))
	{
		if (have_new_line(append_result) == 1)
		{
			append_result = ft_strrchr(append_result, '\n', 1);
			append_result = ft_strjoin(append_result, "\n\0");
			return (append_result);
		}
		append_result = ft_strrchr(append_result, '\n', 1);
	}
	return (NULL);
}

char	*handle_cache(char *cache)
{
	char	*result;

	if (have_new_line(cache))
		result = handle_new_line(cache);
	else
		result = ft_strdup(cache);
	if (!result)
		return (NULL);
	return (result);
}

char	*reads_new_line(int fd)
{
	int		char_read;
	char	*temp;
	char	*buf;

	temp = NULL;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	char_read = read(fd, buf, BUFFER_SIZE);
	if (char_read < 0)
		return (NULL);
	temp = malloc((char_read + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, buf, char_read + 1);
	free (buf);
	return (temp);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 3;
	fd = open("./example2.txt", O_RDONLY);
	while (i-- > 0)
		printf("%s", new_get_next_line(fd));
}