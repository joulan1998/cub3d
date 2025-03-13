/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_remain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:41:42 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 16:16:40 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	draw_line_mini(t_root *root, int end_y, int end_x, int color)
{
	int		i;
	double	x;
	double	y;
	double	length;
	t_pos	*add;

	x = end_x - (*(root->player->player_x) * SCALE);
	y = end_y - (*(root->player->player_y) * SCALE);
	length = sqrt(x * x + y * y);
	add = create_pos(x / length, y / length);
	x = *(root->player->player_x) * SCALE;
	y = *(root->player->player_y) * SCALE;
	i = 0;
	while (i < length)
	{
		my_mlx_pixel_put(&root->mlx_img, (int)round(x), (int)round(y), color);
		x += add->x_pos;
		y += add->y_pos;
		i++;
	}
}

void	render_dir_mini(t_root *root)
{
	root->player->rot_angl += root->player->turndir * 0.4;
	draw_line_mini(root,
		(*(root->player->player_y) + ((sin(root->player->rot_angl))
				* TILE_SIZE)) * SCALE,
		(*(root->player->player_x) + ((cos(root->player->rot_angl))
				* TILE_SIZE)) * SCALE,
		YELLOW);
}

void	sqr_mini(t_root *root, int y, int x, int color)
{
	int	my_x;
	int	my_y;

	my_x = x;
	my_y = y;
	while (y < (my_y + TILE_SIZE))
	{
		x = my_x;
		while (x < (my_x + TILE_SIZE))
		{
			if ((!(y % TILE_SIZE) && !(y % 10))
				|| (!(x % 10) && !(x % TILE_SIZE)))
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
