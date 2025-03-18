/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:34:35 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/16 16:10:19 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/cub3d.h"

void	move_up(t_root *root)
{
	float	angle;
	float	movestep;
	float	new_y;
	float	new_x;
	t_pos	*cur_pos;

	if (!root || !root->player || !root->player->player_x
		|| !root->player->player_y)
		return ;
	root->player->walkdir = 1;
	angle = root->player->rot_angl;
	movestep = root->player->walkdir * root->player->walkspeed * 0.2;
	new_y = *root->player->player_y + sin(angle) * movestep;
	new_x = *root->player->player_x + cos(angle) * movestep;
	if (!maphaswallat(root, new_y, new_x))
	{
		cur_pos = create_pos(*root->player->player_x / TILE_SIZE,
				*root->player->player_y / TILE_SIZE);
		root->map[(int)cur_pos->y_pos][(int)cur_pos->x_pos] = FLOOR;
		*root->player->player_y = new_y;
		*root->player->player_x = new_x;
		root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER;
		free(cur_pos);
	}
}

void	move_down(t_root	*root)
{
	float	angle;
	float	movestep;
	float	new_y ;
	float	new_x ;
	t_pos	*cur_pos;

	if (!root || !root->player || !root->player->player_x
		|| !root->player->player_y)
		return ;
	root->player->walkdir = -1;
	angle = root->player->rot_angl;
	movestep = -1 * root->player->walkdir * root->player->walkspeed * -0.2;
	new_y = *root->player->player_y + sin(angle) * movestep;
	new_x = *root->player->player_x + cos(angle) * movestep;
	if (!maphaswallat(root, new_y, new_x))
	{
		cur_pos = create_pos(*root->player->player_x / TILE_SIZE,
				*root->player->player_y / TILE_SIZE);
		root->map[(int) cur_pos->y_pos][(int) cur_pos->x_pos] = FLOOR;
		*root->player->player_y = new_y;
		*root->player->player_x = new_x;
		root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER;
		free(cur_pos);
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
	{
		free(root->mlx);
		free(root->win);
		free(root->player->player_x);
		free(root->player->player_y);
		free(root->player);
		free(root->map);
		free(root->mlx_img.img);
		exit (111);
	}
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
