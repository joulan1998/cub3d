/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:36:58 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool	parse_color_param(t_params *params, t_tracker *tracker,
	char **splited_line, bool is_floor)
{
	if (is_floor)
	{
		if (tracker->floor_tracker)
			return (tracker->found_duplicate = true, false);
		tracker->floor_tracker = true;
		params->floor_color = parse_color(splited_line);
	}
	else
	{
		if (tracker->ceiling_tracker)
			return (tracker->found_duplicate = true, false);
		tracker->ceiling_tracker = true;
		params->ceiling_color = parse_color(splited_line);
	}
	return (true);
}

static int	count_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	convert_rgb(char **rgb, char **splited_line)
{
	int	r;
	int	g;
	int	b;

	if (arr_len1(rgb) != 3)
		return (-1);
	r = ft_atoi1(rgb[0]);
	g = ft_atoi1(rgb[1]);
	b = ft_atoi1(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	parse_color(char **splited_line)
{
	char	**rgb;
	char	*trimmed_line;
	int		color;

	color = 0;
	if (count_commas(splited_line[1]) != 2)
		return (print_message(PARSING_ERROR, RGB_ERROR), -1);
	trimmed_line = ft_strtrim1(splited_line[1], "\n");
	rgb = ft_split(trimmed_line, ',');
	if (!rgb)
		return (print_message(PARSING_ERROR, SPLIT_FAILED), -1);
	color = convert_rgb(rgb, splited_line);
	free_strings(rgb);
	free(trimmed_line);
	return (color);
}
