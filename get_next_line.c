/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/20 19:52:51 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	return (handle_result(&buf, fd));
}

char	*handle_result(char **buf, int fd)
{
	char	*result;
	int		true;

	true = 0;
	result = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (*(buf[0]))
	{
		result = ft_strlcpy(result, *buf, ft_strlen(*buf) + 1);
		if (have_new_line(result) && true++)
			result = handle_new_line(result);
	}
	if (!true)
		result = reads_new_line(*buf, fd, &result);
	*buf = ft_strrchr(*buf, '\n', 0);
	if (result && result[0] == '\0')
	{
		free(result);
		result = NULL;
	}
	return (result);
}

char	*reads_new_line(char *buf, int fd, char **result)
{
	int		char_read;
	char	*temp;

	char_read = 1;
	temp = NULL;
	while (char_read)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
			return (*result);
		else if (char_read < BUFFER_SIZE)
		{
			temp = malloc((char_read + 1) * sizeof(char));
			if (!temp)
				return (NULL);
			temp = ft_strlcpy(temp, buf, char_read + 1);
			*result = ft_strjoin(*result, temp);
		}
		if (!temp)
			*result = ft_strjoin(*result, buf);
		free(temp);
		if (have_new_line(*result))
			return (*result = handle_new_line(*result));
	}
	return (*result);
}

char	*handle_new_line(char *result)
{
	while (have_new_line(result))
	{
		if (have_new_line(result) == 1)
		{
			result = ft_strrchr(result, '\n', 1);
			result = ft_strjoin(result, "\n\0");
			return (result);
		}
		result = ft_strrchr(result, '\n', 1);
	}
	return (NULL);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 3;
	fd = open("./example2.txt", O_RDONLY);
	while (i-- > 0)
		printf("%s", get_next_line(fd));
}
