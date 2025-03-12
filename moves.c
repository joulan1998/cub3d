/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:34:35 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 16:45:35 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
void	move_up(t_root *root)
{
	float	angle;
	float	movestep;
	float	new_y;
	float	new_x;
	int		current_tile_x;
	int		current_tile_y;

	if (!root || !root->player || !root->player->player_x || !root->player->player_y)
		return ;
	root->player->walkdir = 1;
	angle = root->player->rot_angl;
	movestep = root->player->walkdir * root->player->walkspeed * 0.2;
	new_y = *root->player->player_y + sin(angle) * movestep;
	new_x = *root->player->player_x + cos(angle) * movestep;
	if (!maphaswallat(root, new_y, new_x))
	{
		current_tile_x = *root->player->player_x / TILE_SIZE;
		current_tile_y = *root->player->player_y / TILE_SIZE;
		root->map[current_tile_y][current_tile_x] = FLOOR;
		*root->player->player_y = new_y;
		*root->player->player_x = new_x;
		root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER;
	}
}

void	move_down(t_root	*root)
{
	float	angle;
	float	movestep;
	float	new_y ;
	float	new_x ;
	int		current_tile_x;
	int		current_tile_y;

	if (!root || !root->player || !root->player->player_x || !root->player->player_y)
		return ;
	root->player->walkdir = -1;
	angle = root->player->rot_angl;
	movestep = -1 * root->player->walkdir * root->player->walkspeed * -0.2;
	new_y = *root->player->player_y + sin(angle) * movestep;
	new_x = *root->player->player_x + cos(angle) * movestep;
	if (!maphaswallat(root, new_y, new_x))
	{
		current_tile_x = *root->player->player_x / TILE_SIZE;
		current_tile_y = *root->player->player_y / TILE_SIZE;
		root->map[current_tile_y][current_tile_x] = FLOOR;
		*root->player->player_y = new_y;
		*root->player->player_x = new_x;
		root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER;
	}
}

void	move_right(t_root *root)
{
	root->player->turndir = 1;
}

void	move_left(t_root *root)
{
	root->player->turndir = -1;
}

int	move_player(int keycode, t_root	*root)
{
	if (keycode == 53)
		exit (1);
	else
	{
		if (keycode == 13 || keycode == 126)
			move_up(root);
		else if (keycode == 125 || keycode == 1)
			move_down(root);
		else if (keycode == 124 || keycode == 2)
			move_right(root);
		else if (keycode == 123 || keycode == 0)
			move_left(root);
		update(&root);
		root->player->turndir = 0;
		root->player->walkdir = 0;
	}
	return (0);
}
