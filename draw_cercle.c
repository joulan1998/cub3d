/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cercle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:35:06 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 15:19:54 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_circle(t_root *root, t_pos *cnt_cor, int color, int radius)
{
	int	x;
	int	y;

	y = (int)cnt_cor->y_pos - radius;
	x = (int)cnt_cor->x_pos - radius;
	while (y <= ((int)cnt_cor->y_pos + radius))
	{
		while (x <= ((int)cnt_cor->x_pos + radius))
		{
			if (((x - (int)cnt_cor->x_pos) * (x - (int)cnt_cor->x_pos)
					+ (y - (int)cnt_cor->y_pos)
					* (y - (int)cnt_cor->y_pos)) <= (radius * radius))
				my_mlx_pixel_put(&root->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
	free(cnt_cor);
}
