/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:44:58 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool	ft_isspace1(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*strtrim_texture(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (s1 && !set)
		return ((char *)s1);
	result = NULL;
	if (s1 && set)
	{
		start = 1;
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
