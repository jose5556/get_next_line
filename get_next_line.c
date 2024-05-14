/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/14 20:16:50 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*buf;
	//static char	*text[FOPEN_MAX];

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		checks_new_line(buf);
	}
	buf = ft_strdup(ft_strrchr(buf, '\n'));
	write (1, "l", 1);
	if (!buf)
		return (NULL);
	return (buf);
}

char	*checks_new_line(char *buf)
{
	int		i;
	char	*second_part;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			second_part = ft_substr(second_part, i, ft_strlen(buf));
			break ;
		}
		i++;
	}
	//buf = ft_strrchr(buf, "\n");
	return (second_part);
}

int	main(void)
{
	int	fd;

	fd = open("./example2.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
