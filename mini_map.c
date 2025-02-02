/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:41:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/02/02 19:04:32 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static int pro;

void draw_line_mini(t_root *root, int start_y , int start_x, int  end_y ,int end_x, int color)
{

	int i;
	double x = end_x - start_x;
	double y = end_y - start_y;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;
	x = start_x;
	y = start_y;

	for (i = 0; i < length; i += 1)
	{
		my_mlx_pixel_put(&root->mlx_img, (int)round(x), (int)round(y), color);
		x += addx;
		y += addy;
	}
}

void render_dir_mini(t_root *root)
{
	root->player->rotationAngle += root->player->turnDir *0.4; //root->player->turnSpeed;
	draw_line_mini(root,*root->player->player_y *SCALE, *root->player->player_x * SCALE
	, (*(root->player->player_y) + ((sin(root->player->rotationAngle)) *TILE_SIZE)) * SCALE
	, (*(root->player->player_x) + ((cos(root->player->rotationAngle)) * TILE_SIZE)) * SCALE
	,YELLOW);
}
void draw_squar_mini(t_root *root, int y ,int x,int color,int size, int exist)
{
	int my_x = x;
	int my_y = y;
	while (y < (my_y + size))
	{
		x = my_x;
		while (x < (my_x + size))
		{
			if ((!(y % size) && !(y %10)) || (!(x % 10) && !(x % size)))
			{
				my_mlx_pixel_put(&root->mlx_img, SCALE *x++,  SCALE *y, BLACK);
				continue;
			}
			else
			{
				my_mlx_pixel_put(&root->mlx_img,  SCALE * x++,  SCALE * y, color);
			}
		}
		y++;
	}
}

void render_map_mini(t_root  *root)
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
				draw_squar_mini(root, y*TILE_SIZE,x*TILE_SIZE, WHITE, TILE_SIZE, 0);
			else if (root->map[y][x] == FLOOR)
				draw_squar_mini(root, y*TILE_SIZE,x*TILE_SIZE, BLACK, TILE_SIZE, 0);
			else if (root->map[y][x] == PLAYER)
			{
				draw_squar_mini(root, y *TILE_SIZE,x*TILE_SIZE, BLACK, TILE_SIZE, 0);
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

void mini_cast(t_root *root)
{
	float rayangle = root->player->rotationAngle - (FOV / 2);
	t_ray rays[NUM_RAYS];
	int i = 0;
	while (i < NUM_RAYS)
	{
		// cast_ray(root, &rays[i], rayangle, i);
		// render_wall(root, &rays[i], i);
		rayangle += FOV / NUM_RAYS;
		i++;
	}
}
void mini_map(t_root **root)
{
	render_map_mini(*root);
	render_player(*root);
	render_dir_mini(*root);
	mini_cast(*root);
}