/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:21:43 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/21 18:53:59 by ael-garr         ###   ########.fr       */
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
                    y++;
                    continue;
                }
                if (!(x % size))
                {
                    x++;
                    continue;
                }
                else
                    mlx_pixel_put(root->mlx, root->win,x++,y, color);
            }
            y++;
        }
}
void   parsing(t_root *root)
{
    int my_y = 0;
    int my_x = 0;

    while(my_y < root->map_h)
    {
        my_x = 0;
        while (my_x < root->map_w)
        {
            if (root->map[my_y][my_x] == WALL)
            {
                
                // mlx_string_put(root->mlx, root->win,50,50,RED, "tesyyyyyyyyt");
                draw_squar(root, (my_y * TILE_SIZE), (my_x * TILE_SIZE),RED,TILE_SIZE,0);
            }
            else if (root->map[my_y][my_x] == FLOOR)
            {

                draw_squar(root, (my_y * TILE_SIZE),(my_x * TILE_SIZE),GREEN,TILE_SIZE,0);
            }
            else if (root->map[my_y][my_x] == PLAYER)
            {
                root->player->player_y = my_y;
                root->player->player_x = my_x;
                draw_squar(root, (my_y * TILE_SIZE), (my_x * TILE_SIZE),GREEN,TILE_SIZE,0);
            }
            my_x++;
        }
        my_y++;
    }
}