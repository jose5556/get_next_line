/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/20 17:42:50 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf)
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	return (reads_new_line(&buf, fd));
}

char	*reads_new_line(char **buf, int fd)
{
	char	*result;
	int		false;

	false = 1;
	result = NULL;
	if (*(buf[0]))
	{
		result = ft_strlcpy(result, *buf, ft_strlen(*buf) + 1);
		if (have_new_line(result) && false--)
			result = handle_new_line(result);
	}
	while (read(fd, *buf, BUFFER_SIZE) > 0 && false)
	{
		result = ft_strjoin(result, *buf);
		if (have_new_line(result))
		{
			result = handle_new_line(result);
			break ;
		}
	}
	*buf = ft_strrchr(*buf, '\n', 0);
	if (result && result[0] == '\0')
	{
		free(result);
		result = NULL;
	}
	return (result);
}

char	*handle_new_line(char *result)
{
	while (have_new_line(result))
	{
		if (have_new_line(result) == 1)
		{
			result = ft_strrchr(result, '\n', 1);
			result = ft_strjoin(result, "\n\0");
			break ;
		}
		result = ft_strrchr(result, '\n', 1);
	}
	return (result);
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
