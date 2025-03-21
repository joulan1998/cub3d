/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:29:05 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static bool	validate_horizontal_borders(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (params->map[0][i])
	{
		if (params->map[0][i] != '1' && !ft_isspace1(params->map[0][i]))
			return (false);
		i++;
	}
	j = arr_len1(params->map) - 1;
	i = 0;
	while (params->map[j][i])
	{
		if (params->map[j][i] != '1' && !ft_isspace1(params->map[j][i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_player(char **map)
{
	bool	found_the_player;
	int		i;

	i = 0;
	while (map[i])
	{
		if (found_player_position(map[i]) == true)
		{
			if (found_the_player == true)
				return (print_message(PARSING_ERROR, MULTIPLE_PLAYERS), false);
			found_the_player = true;
		}
		i++;
	}
	return (found_the_player);
}

static bool	check_segment(t_params *params, int i,
		size_t start, size_t len_curr)
{
	size_t	j;

	j = start;
	while (j < len_curr && j < start)
		j++;
	while (j < len_curr)
	{
		if (params->map[i][j] == '0'
			|| (found_player_position(params->map[i] + j)))
			return (false);
		j++;
	}
	return (true);
}

static bool	check_extended_zeros(t_params *params)
{
	int		i;
	int		size;
	size_t	len_prev;
	size_t	len_curr;
	size_t	len_next;

	size = arr_len1(params->map);
	i = 1;
	while (i < size - 1)
	{
		len_prev = ft_strlen1(params->map[i - 1]);
		len_curr = ft_strlen1(params->map[i]);
		len_next = ft_strlen1(params->map[i + 1]);
		if (len_curr > len_prev || len_curr > len_next)
		{
			if (len_curr > len_prev)
				if (!check_segment(params, i, len_prev, len_curr))
					return (false);
			if (len_curr > len_next)
				if (!check_segment(params, i, len_next, len_curr))
					return (false);
		}
		i++;
	}
	return (true);
}

bool	is_valid_map(t_params *params)
{
	int		i;
	int		j;
	bool	valid;

	if (arr_len1(params->map) < 3)
		return (print_message(PARSING_ERROR, INVALID_MAP), false);
	if (validate_textures(params) == false)
		return (false);
	if (is_valid_player(params->map) == false)
		return (print_message(PARSING_ERROR, INVALID_PLAYER), false);
	if (validate_horizontal_borders(params) == false)
		return (print_message(PARSING_ERROR, INVALID_MAP_BORDERS), false);
	if (validate_map_content(params) == false)
		return (print_message(PARSING_ERROR, INVALID_MAP_CONTENT), false);
	if (check_extended_zeros(params) == false)
		return (print_message(PARSING_ERROR, "INVALID_MAP_CONTENT"), false);
	return (true);
}
