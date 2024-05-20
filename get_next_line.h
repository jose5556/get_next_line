/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:54 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/20 21:30:36 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strrchr(char *s, int c, int last);
char	*ft_strdup(const char *s);
int		have_new_line(char *buf);

char	*get_next_line1(int fd);
char	*new_get_next_line(int fd);

char	*handle_result1(char **buf, int fd);
char	*handle_cache(char *cache);

char	*handle_new_line1(char *result);
char	*handle_new_line(char *result);

char	*reads_new_line1(char *buf, int fd, char *result);
char	*reads_new_line(int fd);

#endif