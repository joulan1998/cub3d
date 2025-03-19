/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:41 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 14:41:07 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

bool	parse_map_line(char *line, t_map **map,
	t_tracker *tracker, t_params *params)
{
	if (tracker->no_tracker == false || tracker->so_tracker == false
		|| tracker->we_tracker == false || tracker->ea_tracker == false
		|| tracker->floor_tracker == false || tracker->ceiling_tracker == false)
		return (print_message(PARSING_ERROR, MAP_ORDER_ERROR), false);
	if (params->floor_color == -1 || params->ceiling_color == -1)
		return (print_message(PARSING_ERROR, RGB_ERROR), false);
	if (check_if_valid(tracker, line) == false)
		return (print_message(PARSING_ERROR, INVALID_MAP), false);
	if (check_if_empty_line(line) == false)
		ft_addlst(map, ft_createlst(line));
	return (true);
}

static char	*ft_strdup_replace_spaces(char *src)
{
	char	*dest;
	size_t	len;
	size_t	i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (src[i] == ' ')
			dest[i] = '1';
		else
			dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

bool	extract_cleaned_map(t_params *params, t_map **map)
{
	int		i;
	int		size;
	t_map	*current;

	i = 0;
	size = ft_sizelst(*map);
	if (size <= 0)
		return (ft_cleanlst(map), printf(INVALID_MAP), false);
	params->map = malloc((size + 1) * sizeof(char *));
	if (!params->map)
		return (ft_cleanlst(map),
			print_message(PARSING_ERROR, MALLOC_ERROR), false);
	params->map_height = size;
	current = *map;
	while (i < size && current != NULL)
	{
		params->map[i] = ft_strdup_replace_spaces(current->line);
		if (!params->map[i])
			return (ft_cleanlst(map),
				print_message(PARSING_ERROR, MALLOC_ERROR), false);
		current = current->next;
		i++;
	}
	return (params->map[i] = NULL, ft_cleanlst(map), true);
}

bool	is_map_line(char *line)
{
	int	i;
	int	has_content;

	if (!line || !*line)
		return (false);
	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (!ft_strchr(VALID_MAP_CHARS, line[i]))
			return (false);
		if (ft_strchr(MAP_CONTENT_CHARS, line[i]))
			has_content = 1;
		i++;
	}
	return (has_content == 1);
}
