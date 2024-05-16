/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/16 01:18:35 by joseoliv         ###   ########.fr       */
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

	result = NULL;
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		if (!have_new_line(buf))
		{
			if (!result)
			{
				result = ft_strlcpy(result, buf, ft_strlen(buf) + 1);
				continue ;
			}
			result = ft_strjoin(result, buf);
			continue ;
		}
	while (have_new_line(result) > 1)
	{
		result = ft_strjoin(result, ft_strrchr(buf, '\n'));
	}
	result = ft_strjoin(result, buf);
	}
	
	return (result);
}

int	main(void)
{
	int	fd;

	fd = open("./example2.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
