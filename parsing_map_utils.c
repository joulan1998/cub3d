/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:37:51 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	is_valid_character(char c)
{
	if (c == '0' || c == '1' | c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

bool	check_if_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (true);
	if (line[0] && line[0] == '\n')
		return (true);
	return (false);
}

bool	check_if_valid(t_tracker *tracker, char *line)
{
	int	i;

	i = 0;
	if (!tracker || !line)
		return (false);
	while (line[i])
	{
		if (!ft_strchr1(VALID_MAP_CHARS, line[i]))
			return (false);
		if (ft_strchr1(MAP_CONTENT_CHARS, line[i]) && tracker->found_empty_line)
			return (false);
		i++;
	}
	tracker->found_empty_line = check_if_empty_line(line);
	return (true);
}
