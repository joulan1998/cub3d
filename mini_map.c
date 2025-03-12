/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:41:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 17:47:41 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static int pro;

void	draw_line_mini(t_root *root, int end_y, int end_x, int color)
{
	int		i;
	double	x;
	double	y;
	double	length;
	double	addx;
	double	addy;

	x = end_x - (*(root->player->player_x)  * SCALE);
	y = end_y - (*(root->player->player_y) * SCALE);
	length = sqrt(x * x + y * y);
	addx = x / length;
	addy = y / length;
	x = *(root->player->player_x) * SCALE;
	y = *(root->player->player_y) * SCALE;
	i = 0;
	while (i < length)
	{
		my_mlx_pixel_put(&root->mlx_img, (int)round(x), (int)round(y), color);
		x += addx;
		y += addy;
		i++;
	}
}

void	render_dir_mini(t_root *root)
{
	root->player->rot_angl += root->player->turndir * 0.4;
	draw_line_mini(root,
		(*(root->player->player_y) + ((sin(root->player->rot_angl)) * TILE_SIZE)) * SCALE,
		(*(root->player->player_x) + ((cos(root->player->rot_angl)) * TILE_SIZE)) * SCALE,
		YELLOW);
}

void	sqr_mini(t_root *root, int y, int x, int color, int size)
{
	int	my_x;
	int	my_y;

	my_x = x;
	my_y = y;
	while (y < (my_y + size))
	{
		x = my_x;
		while (x < (my_x + size))
		{
			if ((!(y % size) && !(y % 10)) || (!(x % 10) && !(x % size)))
			{
				my_mlx_pixel_put(&root->mlx_img, SCALE * x++, SCALE * y, BLACK);
				continue ;
			}
			else
				my_mlx_pixel_put(&root->mlx_img, SCALE * x++, SCALE * y, color);
		}
		y++;
	}
}

void	render_map_mini(t_root *root)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < root->map_h)
	{
		x = 0;
		while (x < root->map_w)
		{
			if (root->map[y][x] == WALL)
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, WHITE, TILE_SIZE);
			else if (root->map[y][x] == FLOOR)
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, BLACK, TILE_SIZE);
			else if (root->map[y][x] == PLAYER)
			{
				sqr_mini(root, y * TILE_SIZE, x * TILE_SIZE, BLACK, TILE_SIZE);
				if (pro == 0)
				{
					*(root->player->player_y) = (y * TILE_SIZE) + 20;
					*(root->player->player_x) = (x * TILE_SIZE) + 20;
					pro = 1;
				}
			}
			x++;
		}
		y++;
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
		// cast_ray(root, &rays[i], rayangle, i);
		// render_wall(root, &rays[i], i);
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
