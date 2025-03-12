/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:21:43 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 16:57:57 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_squar(t_root *root, int y, int x, int color, int size, int exist)
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
				my_mlx_pixel_put(&root->mlx_img, x++, y, BLACK);
				continue ;
			}
			else
			{
				my_mlx_pixel_put(&root->mlx_img, x++, y, color);
			}
		}
		y++;
	}
}
