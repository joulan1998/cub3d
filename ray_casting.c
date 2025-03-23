/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:56:47 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/22 17:52:42 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

// void draw_line(t_root *root, int end_x, int end_y, int color)
// {
//     int start_x = (int)(*(root->player->player_x) * SCALE);
//     int start_y = (int)(*(root->player->player_y) * SCALE);
//     int dx = abs(end_x - start_x);
//     int dy = abs(end_y - start_y);
//     int sx = (start_x < end_x) ? 1 : -1;
//     int sy = (start_y < end_y) ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (1)
//     {
//         // Draw the current pixel
//         my_mlx_pixel_put(&root->mlx_img, start_x, start_y, color);

//         // Check if we've reached the endpoint
//         if (start_x == end_x && start_y == end_y)
//             break;

//         // Calculate the next pixel
//         e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             start_x += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             start_y += sy;
//         }
//     }
// }