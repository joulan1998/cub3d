/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:22:12 by abzaiz            #+#    #+#             */
/*   Updated: 2025/03/19 16:18:55 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_params(t_params *params)
{
	params->map = NULL;
	params->no_texture = NULL;
	params->so_texture = NULL;
	params->we_texture = NULL;
	params->ea_texture = NULL;
	params->floor_color = -1;
	params->ceiling_color = -1;
	params->map_width = 0;
	params->map_height = 0;
}
