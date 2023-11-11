/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:43:50 by ulyildiz          #+#    #+#             */
/*   Updated: 2023/11/11 16:22:12 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>


static size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!(s))
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sourc;
	size_t			i;

	dest = (unsigned char *)dst;
	sourc = (unsigned char *)src;
	i = 0;
	if (dest == NULL && sourc == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = sourc[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	j = ft_strlen(s2);
	i = ft_strlen(s1);
	s3 = (char *)malloc(i + j + 1);
	if (s3 == NULL)
		return (NULL);
	ft_memcpy(s3, s1, i);
	ft_memcpy(s3 + i, s2, j);
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
