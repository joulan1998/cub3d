/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:40:50 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	parse_param_line(t_params *params, t_tracker *tracker,
	char **splited_line)
{
	if (ft_strcmp1(splited_line[0], "NO") == 0)
		return (parse_texture_line(1, params, tracker, splited_line));
	else if (ft_strcmp1(splited_line[0], "SO") == 0)
		return (parse_texture_line(2, params, tracker, splited_line));
	else if (ft_strcmp1(splited_line[0], "WE") == 0)
		return (parse_texture_line(3, params, tracker, splited_line));
	else if (ft_strcmp1(splited_line[0], "EA") == 0)
		return (parse_texture_line(4, params, tracker, splited_line));
	else if (ft_strcmp1(splited_line[0], "F") == 0)
		return (parse_color_param(params, tracker,
				splited_line, true));
	else if (ft_strcmp1(splited_line[0], "C") == 0)
		return (parse_color_param(params, tracker, splited_line, false));
	else
		return (tracker->found_unkown = true, false);
	return (true);
}

bool	parse_file_line(char *line, t_tracker *tracker, t_params *params)
{
	char	**splited_line;

	if (line[0] == '\n' && tracker->found_the_map == true)
		return (true);
	if (line[0] == '\n')
		return (false);
	if (tracker->found_the_map == true)
		return (true);
	if (is_map_line(line))
		return (tracker->found_the_map = true, true);
	splited_line = split_two(line);
	if (splited_line == NULL)
		return (false);
	if (is_map_line(line))
		return (tracker->found_the_map = true,
			free_strings(splited_line), true);
	if (parse_param_line(params, tracker, splited_line) == false)
		return (free_strings(splited_line), false);
	return (free_strings(splited_line), tracker->found_the_map);
}
