/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abzaiz <abzaiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:29:21 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 14:29:01 by abzaiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static bool	parse_file_content(int fd, t_tracker *tracker,
		t_params *params, t_map **map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (parse_file_line(line, tracker, params) == true)
		{
			if (parse_map_line(line, map, tracker, params) == false)
				return (ft_cleanlst(map), free(line), false);
		}
		else
		{
			if (tracker->found_unkown == true)
				return (print_message(PARSING_ERROR, UNKOWN_OBJECT),
					free(line), close(fd), ft_cleanlst(map), false);
			if (tracker->found_duplicate == true)
				return (print_message(PARSING_ERROR, FOUND_DUPLICATE),
					free(line), close(fd), ft_cleanlst(map), false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

bool	parser(t_params *params, char *map_file)
{
	t_map		*map;
	t_tracker	tracker;
	int			fd;
	bool		extracted;

	map = NULL;
	ft_memset(&tracker, 0, sizeof(tracker));
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_message(OPEN_ERROR, map_file), false);
	if (parse_file_content(fd, &tracker, params, &map) == false)
		return (close(fd), false);
	close(fd);
	if (tracker.found_the_map == false)
		return (print_message(PARSING_ERROR, INVALID_MAP),
			ft_cleanlst(&map), false);
	extracted = extract_cleaned_map(params, &map);
	if (extracted == false)
		return (print_message(PARSING_ERROR, "Extraction Error"),
			ft_cleanlst(&map), false);
	return (is_valid_map(params));
}
