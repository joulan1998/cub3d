/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:45 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	ft_isdigit1(int c)
{
	return (c >= '0' && c <= '9');
}

static void	*ft_memchr1( void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	if (n < 1)
		return (NULL);
	index = 0;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		if (ptr[index] == (unsigned char) c)
			return ((void *)(s + index));
		index++;
	}
	return (NULL);
}

char	*ft_strchr1( char *s, int c)
{
	return ((char *)ft_memchr1(s, c, ft_strlen1(s) + 1));
}

size_t	ft_strlcpy1(char *dst, char *src, size_t dstsize)
{
	size_t	index;
	size_t	srcsize;

	index = 0;
	srcsize = ft_strlen1(src);
	if (dstsize == 0)
		return (srcsize);
	while (src[index] && index < dstsize - 1)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (srcsize);
}

char	*ft_strtrim1(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (s1 && !set)
		return ((char *)s1);
	result = NULL;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen1(s1);
		while (s1[start] && ft_strchr1(set, s1[start]))
			start++;
		while (end > start && s1[end - 1] && ft_strchr1(set, s1[end - 1]))
			end--;
		result = (char *)malloc(sizeof(char) * (end - start + 1));
		if (result)
			ft_strlcpy1(result, s1 + start, end - start + 1);
	}
	return (result);
}
