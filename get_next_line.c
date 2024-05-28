/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:09:43 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/28 13:38:26 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	result = filter_buffer(buffer);
	buffer = handle_next(buffer);
	return (result);
}

char	*filter_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while(buffer[i] && buffer[i] != '\n')
		i++;
	result = ft_calloc(i + 2, sizeof(char));
	j = 0;
	while (j < i)
	{
		result[j] = buffer[j];
		j++;
	}
	j++;
	if (buffer[j] && buffer[j] == '\n')
		result[j] = '\n';
	return (result);
}

char	*read_file(int fd, char *buffer)
{
	char	*temp_buf;
	int		bytes_read;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	temp_buf = ft_calloc(BUFFER_SIZE + 1, 1);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buf);
			return (NULL);
		}
		temp_buf[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, temp_buf);
		if (ft_strchr(temp_buf, '\n'))
			break ;
	}
	free(temp_buf);
	return (buffer);
}

char	*handle_next(char *buffer)
{
	char	*result;
	char	*ptr;
	int		i;

	ptr = buffer;
	while (*buffer && *buffer != '\n')
		buffer++;
	if (!(*buffer))
	{
		free(ptr);
		return (NULL);
	}
	result = ft_calloc(ft_strlen(buffer + 1) + 1, sizeof(char));
	if (!result)
	{
		free (ptr);
		return (NULL);
	}
	buffer++;
	i = 0;
	while (*buffer)
		result[i++] = *buffer++;
	free (ptr);
	return (result);
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
		printf("line %d [%s] ", i, line);
		free(line);
	}
	close(fd);
	return (0);
}