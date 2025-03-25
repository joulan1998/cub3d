/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:21:43 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/25 14:42:39 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_squar(t_root *root, int y, int x, int color)
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

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free((map)[i]);
		i++;
	}
	free(map);
}

int	ft_exit(t_root *root)
{
	ft_print("GOOD BY!\n");
	exit(0);
}
