/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:28:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 22:39:49 by ael-garr         ###   ########.fr       */
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
	if (local_x < 0)
		local_x = 0;
	if (local_y < 0)
		local_y = 1;
	if (local_x > ft_strlen(root->map[local_y]) - 1)
		return (0);
	else
		return (root->map[local_y][local_x] == WALL);
}

void	render_dir(t_root *root)
{
	root->player->rot_angl += root->player->turndir * 0.4;
	draw_line(root,
		*(root->player->player_y) + (sin(root->player->rot_angl) * TILE_SIZE),
		*(root->player->player_x) + cos(root->player->rot_angl) * TILE_SIZE,
		RED);
}

void	local_pro(t_root **root, int x, int y)
{
	*((*root)->player->player_y) = (y * TILE_SIZE) + 20;
	*((*root)->player->player_x) = (x * TILE_SIZE) + 20;
	(*root)->p_sym = (*root)->map[y][x];
}

bool	is_player(char c)
{
	return ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'));
}

void	render_map(t_root *root)
{
	int			y;
	int			x;

	y = 0;
	while (y++ < root->map_h)
	{
		x = -1;
		while (++x < ft_strlen(root->map[y]))
		{
			if (is_player(root->map[y][x]) == true)
			{
				*(root->player->player_y) = (y * TILE_SIZE) + 20;
				*(root->player->player_x) = (x * TILE_SIZE) + 20;
				root->p_sym = root->map[y][x];
			}
		}
	}
}
