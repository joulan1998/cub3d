/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:41:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/22 12:54:48 by ael-garr         ###   ########.fr       */
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
		// while (++x < root->map_w)
		while (++x < ft_strlen1(root->map[y]))
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

void	mini_cast(t_root *root, int rays_nbr)
{
	float	rayangle;
	t_ray	rays[rays_nbr];
	int		i;

	rayangle = root->player->rot_angl - ((60 * (M_PI / 180)) / 2);
	i = 0;
	while (i < rays_nbr)
	{
		rayangle += (60 * (M_PI / 180)) / rays_nbr;
		i++;
	}
}

void	mini_map(t_root **root)
{
	render_map_mini(*root);
	render_dir_mini(*root);
	// mini_cast(*root, ((*root)->map_w * TILE_SIZE) / WALL_STRIPE);
}
