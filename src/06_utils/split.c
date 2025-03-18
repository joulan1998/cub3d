/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:43:28 by abzaiz            #+#    #+#             */
/*   Updated: 2025/02/11 16:19:18 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static int	count_words(char	*s, char c)
{
	int	counter;

	counter = 0;
	while (*s)
	{
		while (*s && (*s == c || *s == '\n'))
			s++;
		if (*s && *s != c)
		{
			while (*s && (*s != c && *s != '\n'))
				s++;
			counter++;
		}
	}
	return (counter);
}

static int	word_length(char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] && s[index] != c)
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

char	**ft_split(char *s, char c)
{
	char	**result;
	int		index;
	int		words_count;
	int		length_of_word;

	if (s == NULL)
		return (NULL);
	words_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (!result)
		return (NULL);
	index = 0;
	while (index < words_count)
	{
		while (*s == c)
			s++;
		length_of_word = word_length(s, c);
		result[index] = ft_substr(s, 0, length_of_word);
		if (!result[index])
			return (free_memory(result, index));
		index++;
		s += length_of_word;
	}
	result[index] = NULL;
	return (result);
}
