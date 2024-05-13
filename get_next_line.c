/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:32 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/13 06:23:50 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd);

char *get_next_line(int fd)
{
	char	*buffer;

	
	while (read(fd, buffer, 1))
	{
		printf("%s", buffer);
	}
	return (NULL);
}

int	main(void)
{
	int	fd;

	fd = open("./example.txt", O_RDONLY, O_RDONLY);
	get_next_line(fd);
}