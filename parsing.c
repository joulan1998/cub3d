/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:21:43 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/30 18:52:51 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void draw_squar(t_root *root, int y ,int x,int color,int size, int exist)
{
    int my_x = x;
    int my_y = y;
    while (y < (my_y + size))
    {
        x = my_x;
        while (x < (my_x + size))
        {
            if (!(y % size))
            {
                my_mlx_pixel_put(&root->mlx_img, x, y, BLACK);
                x++;
                continue;
            }
            if (!(x % 10) && !(x % size))
            {
                my_mlx_pixel_put(&root->mlx_img, x, y, BLACK);
                x++;
                continue;
            }
            else
            {
                my_mlx_pixel_put(&root->mlx_img, x, y, color);
                x++;
            }
        }
        y++;
    }
}
