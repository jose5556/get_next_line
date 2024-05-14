/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/14 22:39:52 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char		*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	return (reads_new_line(buf, fd));
}

char	*reads_new_line(char *buf, int fd)
{
	char	*result;
	char	*temp;

	result = NULL;
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		if (!have_new_line(buf))
		{
			if (!result)
			{
				ft_strlcpy(result, buf, 10);
				write(1, "s", 1);
			}
			else
			{
				ft_strlcpy(temp, buf, 10);
				result = ft_strjoin(temp, buf);
				write(1, "g", 1);
			}

		}
		result = ft_strjoin(result, ft_strrchr(buf, '\n'));
	}
	return (result);
}

int	main(void)
{
	int	fd;

	fd = open("./example2.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
