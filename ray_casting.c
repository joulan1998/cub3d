/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:56:47 by ael-garr          #+#    #+#             */
/*   Updated: 2025/02/04 19:01:27 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray	*create_ray(float rayAngle)
{
	t_ray	*res;

	res = malloc(sizeof(t_ray));
	if (!res)
		return (NULL);
	res->rayAngle = normalizeAngle(rayAngle);
	res->distance = 0;
	res->wallHitX = 0;
	res->facingDown = (rayAngle > 0 && rayAngle < M_PI);
	res->facingUp = !res->facingDown;
	res->facingRight = (rayAngle > (0.5 * M_PI) || rayAngle > (1.5 * M_PI));
	res->facingLeft = !res->facingRight;
	return (res);
}

void	draw_line(t_root *root, int start_y, int start_x, int  end_y, int end_x, int color)
{
	double	length;
	double	addx;
	double	addy;
	double	x;
	double	y;

	x = end_x - start_x;
	y = end_y - start_y;
	length = sqrt(x * x + y * y);
	addx = x / length;
	addy = y / length;
	x = start_x;
	y = start_y;
	end_x = 0;
	while (end_x < length)
	{
		my_mlx_pixel_put(&root->mlx_img, (int)round(x), (int)round(y), color);
		x += addx;
		y += addy;
		end_x++;
	}
}
