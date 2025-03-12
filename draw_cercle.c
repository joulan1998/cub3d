/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cercle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:35:06 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 15:38:36 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_circle(t_root *root, int cnt_y, int cnt_x, int color, int radius)
{
	int	x;
	int	y;

	y = cnt_y - radius;
	x = cnt_x - radius;
	while (y <= (cnt_y + radius))
	{
		while (x <= (cnt_x + radius))
		{
			if (((x - cnt_x) * (x - cnt_x) + (y - cnt_y) * (y - cnt_y)) <= (radius * radius))
				my_mlx_pixel_put(&root->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}
