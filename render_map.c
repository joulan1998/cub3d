/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:28:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:10 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	maphaswallat(t_root *root, float y, float x)
{
	int	local_x;
	int	local_y;

	if (y < 0 || y >= root->win_h || x < 0 || x >= root->win_w)
		return (1);
	local_x = floor(x / TILE_SIZE);
	local_y = floor(y / TILE_SIZE);
	return (root->map[local_y][local_x] == WALL);
}

void	render_dir(t_root *root)
{
	root->player->rot_angl += root->player->turndir * 0.4; //root->player->turnspeed;
	draw_line(root, *root->player->player_y * SCALE, *root->player->player_x * SCALE,
		*(root->player->player_y) + (sin(root->player->rot_angl) * TILE_SIZE),
		*(root->player->player_x) + cos(root->player->rot_angl) * TILE_SIZE,
		RED);
}

void	render_map(t_root *root)
{
	int		y;
	int		x;
	static int prot;

	x = 0;
	y = 0;
	while (y < root->map_h)
	{
		x = 0;
		while (x < root->map_w)
		{
			if (root->map[y][x] == WALL)
				draw_squar(root, y * TILE_SIZE, x * TILE_SIZE, WHITE, TILE_SIZE, 0);
			else if (root->map[y][x] == FLOOR)
				draw_squar(root, y * TILE_SIZE, x * TILE_SIZE, BLACK, TILE_SIZE, 0);
			if (root->map[y][x] == PLAYER)
			{
				draw_squar(root, y * TILE_SIZE, x * TILE_SIZE, BLACK, TILE_SIZE, 0);
				if (prot == 0)
				{
					*(root->player->player_y) = (y * TILE_SIZE) + 20;
					*(root->player->player_x) = (x * TILE_SIZE) + 20;
					prot = 1;
				}
			}
			x++;
		}
		y++;
	}
}
