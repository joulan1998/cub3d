/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_validation_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:29:57 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

bool	validate_map_content(t_params *params)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = arr_len1(params->map);
	while (i < size)
	{
		j = 0;
		while (params->map[i][j] && params->map[i][j] == ' ')
			j++;
		if (params->map[i][j] != '1')
			return (false);
		j = ft_strlen1(params->map[i]) - 1;
		while (j >= 0 && params->map[i][j] == ' ')
			j--;
		if (params->map[i][j] != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	found_player_position(char *map_line)
{
	if (ft_strchr1(map_line, 'N') || ft_strchr1(map_line, 'S')
		|| ft_strchr1(map_line, 'E') || ft_strchr1(map_line, 'W'))
		return (true);
	return (false);
}
