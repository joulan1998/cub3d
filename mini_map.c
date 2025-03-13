/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:41:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 16:17:47 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	local_prot(t_root **root, int x, int y)
{
	*((*root)->player->player_y) = (y * TILE_SIZE) + 20;
	*((*root)->player->player_x) = (x * TILE_SIZE) + 20;
}

void	render_map_mini(t_root *root)
{
	int			y;
	int			x;
	int static	pro;

	y = -1;
	while (++y < root->map_h)
	{
		x = -1;
		while (++x < root->map_w)
		{
			if (root->map[y][x] == WALL)
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, WHITE);
			else if (root->map[y][x] == FLOOR)
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, BLACK);
			else if (root->map[y][x] == PLAYER)
			{
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, BLACK);
				if (pro == 0)
				{
					local_prot(&root, x, y);
					pro = 1;
				}
			}
		}
	}
}

void	mini_cast(t_root *root)
{
	float	rayangle;
	t_ray	rays[NUM_RAYS];
	int		i;

	rayangle = root->player->rot_angl - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		rayangle += FOV / NUM_RAYS;
		i++;
	}
}

void	mini_map(t_root **root)
{
	render_map_mini(*root);
	render_player(*root);
	render_dir_mini(*root);
	mini_cast(*root);
}
