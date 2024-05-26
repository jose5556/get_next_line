/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:56:44 by joseoliv          #+#    #+#             */
/*   Updated: 2024/05/26 15:00:32 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *s, int c, int last)
{
	int	i;

	if (last)
	{
		i = ft_strlen(s);
		while (i >= 0)
		{
			if (s[i] == (char)c)
			{
				s[i] = '\0';
				return (s);
			}
			i--;
		}
	}
	else
	{
		while (*s)
		{
			if (*s == (char)c)
				return (s + 1);
			s++;
		}
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	result = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (result);
	i = 0;
	j = 0;
	while (s1[j])
		result[i++] = ((char *)s1)[j++];
	j = 0;
	while (s2[j])
		result[i++] = ((char *)s2)[j++];
	result[i] = 0;
	return (result);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1) && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*new_string;
	int		len;

	len = ft_strlen(s);
	new_string = (char *) malloc (len * (sizeof(char)) + 1);
	if (new_string == NULL)
		return (new_string);
	ft_strlcpy(new_string, s, len + 1);
	return (new_string);
}
