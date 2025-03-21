/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:26:03 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:24:00 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	validate_texture_file(char *texture)
{
	int	fd;

	if (!is_valid_file_extension(texture, ".xpm"))
		return (print_message(PARSING_ERROR, INVALID_TEXTURE_EXT), false);
	fd = open(texture, O_RDONLY);
	if (fd == -1)
		return (print_message(PARSING_ERROR, INVALID_TEXTURE_FILE), false);
	close(fd);
	return (true);
}

bool	validate_textures(t_params *params)
{
	if (!validate_texture_file(params->no_texture))
		return (false);
	if (!validate_texture_file(params->so_texture))
		return (false);
	if (!validate_texture_file(params->we_texture))
		return (false);
	if (!validate_texture_file(params->ea_texture))
		return (false);
	return (true);
}

static bool	check_duplicate_texture(t_tracker *tracker, int i)
{
	if ((i == 1 && tracker->no_tracker)
		|| (i == 2 && tracker->so_tracker)
		|| (i == 3 && tracker->we_tracker)
		|| (i == 4 && tracker->ea_tracker))
		return (true);
	return (false);
}

bool	parse_texture_line(int i, t_params *params,
	t_tracker *tracker, char **splited_line)
{
	if (check_duplicate_texture(tracker, i))
		return (tracker->found_duplicate = true, false);
	if (i == 1)
	{
		tracker->no_tracker = true;
		params->no_texture = strtrim_texture(splited_line[1], "\n");
	}
	else if (i == 2)
	{
		tracker->so_tracker = true;
		params->so_texture = strtrim_texture(splited_line[1], "\n");
	}
	else if (i == 3)
	{
		tracker->we_tracker = true;
		params->we_texture = strtrim_texture(splited_line[1], "\n");
	}
	else if (i == 4)
	{
		tracker->ea_tracker = true;
		params->ea_texture = strtrim_texture(splited_line[1], "\n");
	}
	return (true);
}
