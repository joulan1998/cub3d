/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:56:47 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:06 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

t_ray	*create_ray(float rayangle)
{
	t_ray	*res;

	res = malloc(sizeof(t_ray));
	if (!res)
		return (NULL);
	res->rayangle = normalizeangle(rayangle);
	res->distance = 0;
	res->wallhitx = 0;
	res->facingdwn = (rayangle > 0 && rayangle < M_PI);
	res->facingup = !res->facingdwn;
	res->facingright = (rayangle > (0.5 * M_PI) || rayangle > (1.5 * M_PI));
	res->facingleft = !res->facingright;
	return (res);
}

void	draw_line(t_root *root, int end_y, int end_x, int color)
{
	double	length;
	double	addx;
	double	addy;
	double	x;
	double	y;

	x = end_x - *(root->player->player_x) * SCALE;
	y = end_y - *(root->player->player_y) * SCALE;
	length = sqrt(x * x + y * y);
	addx = x / length;
	addy = y / length;
	x = *(root->player->player_x) * SCALE;
	y = *(root->player->player_y) * SCALE;
	end_x = 0;
	while (end_x < length)
	{
		my_mlx_pixel_put(&root->mlx_img, (int)round(x), (int)round(y), color);
		x += addx;
		y += addy;
		end_x++;
	}
}
