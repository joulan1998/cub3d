/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:27 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

size_t	ft_strlen1( char *s)
{
	size_t	result;

	result = 0;
	while (s[result])
		result++;
	return (result);
}

int	ft_strcmp1(char *str1, char *str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp1(char *s1, char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	while (*s1 && *s2 && (*s1 == *s2) && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strrchr1( char *s, int c)
{
	char	*result;

	result = NULL;
	while (*s)
	{
		if (*s == (char)c)
			result = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (result);
}

void	*ft_memset1(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}
