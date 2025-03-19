/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitTwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:50:04 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 15:27:23 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	count_parts(const char *s)
{
	int	counter;
	int	found_space;

	counter = 0;
	found_space = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			while (*s && !ft_isspace(*s))
				s++;
			counter++;
			if (*s)
				found_space = 1;
			while (*s && ft_isspace(*s))
				s++;
			if (*s && found_space)
				counter++;
		}
	}
	if (counter > 2)
		return (2);
	return (counter);
}

static int	identifier_length(const char *s)
{
	int	index;

	index = 0;
	while (s[index] && !ft_isspace(s[index]))
		index++;
	return (index);
}

static void	*free_memory(char **result, int length)
{
	int	index;

	index = 0;
	while (index < length)
		free(result[index++]);
	free(result);
	return (NULL);
}

char	**split_two_helper(char *line, int parts_count,
	int index, char **result)
{
	int	id_len;

	while (*line && ft_isspace(*line))
		line++;
	id_len = identifier_length(line);
	result[index] = ft_substr((char *)line, 0, id_len);
	if (!result[index])
		return (free_memory(result, index));
	index++;
	line += id_len;
	result[index] = ft_strdup((char *)line);
	if (!result[index])
		return (free_memory(result, index));
	index++;
	result[index] = NULL;
	return (result);
}

char	**split_two(char *line)
{
	char	**result;
	int		parts_count;

	if (!line)
		return (NULL);
	parts_count = count_parts(line);
	if (parts_count != 2)
		return (NULL);
	result = malloc(sizeof(char *) * (parts_count + 1));
	if (!result)
		return (NULL);
	return (split_two_helper(line, parts_count, 0, result));
}
