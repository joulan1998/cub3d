/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:34 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 14:46:47 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	length;
	size_t	index;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	index = 0;
	if (length > len)
		length = len;
	substring = (char *)malloc(sizeof(char) * (length + 1));
	if (!substring)
		return (NULL);
	while (index < length)
	{
		substring[index] = s[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		size;
	char	*copy;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	copy = malloc(sizeof(char) * size + 1);
	if (copy == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
		str[j++] = s1[i++];
	i = 0;
	while (i < len2)
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

size_t	arr_len(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	ft_atoi(char *s)
{
	long	result;

	result = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			return (-1);
		s++;
	}
	if (!ft_isdigit(*s))
		return (-1);
	while (ft_isdigit(*s))
	{
		result = result * 10 + (*s - '0');
		if (result > 255)
			return (-1);
		s++;
	}
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s)
		return (-1);
	return ((int)result);
}
