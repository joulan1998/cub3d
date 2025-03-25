/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:41:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/25 14:30:56 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	render_map_mini(t_root *root)
{
	int	y;
	int	x;

	y = -1;
	while (++y < root->map_h)
	{
		x = -1;
		while (++x < ft_strlen(root->map[y]))
		{
			if (root->map[y][x] == WALL)
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, WHITE);
			else
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, BLACK);
		}
	}
}

void	mini_map(t_root **root)
{
	render_map_mini(*root);
	render_dir_mini(*root);
}
