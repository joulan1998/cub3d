#include "../../headers/cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	*ft_memchr( void *s, int c, size_t n)
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

char	*ft_strchr( char *s, int c)
{
	return ((char *)ft_memchr(s, c, ft_strlen(s) + 1));
}

size_t	ft_strlcpy(char *dst,  char *src, size_t dstsize)
{
	size_t	index;
	size_t	srcsize;

	index = 0;
	srcsize = ft_strlen(src);
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

char	*ft_strtrim(char  *s1, char  *set)
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
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (end > start && s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
		result = (char *)malloc(sizeof(char) * (end - start + 1));
		if (result)
			ft_strlcpy(result, s1 + start, end - start + 1);
	}
	return (result);
}
