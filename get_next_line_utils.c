/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:43:50 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/19 18:31:34 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_calloc(size_t count, size_t nbyte)
{
	void	*allc;
	size_t	i;

	i = 0;
	allc = malloc(count * nbyte);
	if (!allc)
		return (NULL);
	while (i < count * nbyte)
	{
		((char *)allc)[i] = '\0';
		i++;
	}
	return (allc);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	return (s3);
}
char	*ft_strchr(const char *string, int searchedChar )
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}