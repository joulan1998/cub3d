/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:21:43 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/26 11:25:21 by ael-garr         ###   ########.fr       */
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
    // mlx_put_image_to_window(root->mlx, root->win, root->mlx_img.img, 0 ,0);
}
// void   parsing(t_root *root)
// {
//     int my_y = 0;
//     int my_x = 0;

//     if (!root->map)
//         exit(puts("map error !!!!"));
//     while(my_y < root->map_h)
//     {
//         my_x = 0;
//         while (my_x < root->map_w)
//         {
//             if (root->map[my_y][my_x] == WALL)
//             {
//                 draw_squar(root, (my_y * TILE_SIZE), (my_x * TILE_SIZE),RED,TILE_SIZE,0);
//             }
//             else if (root->map[my_y][my_x] == FLOOR)
//             {

//                 draw_squar(root, (my_y * TILE_SIZE),(my_x * TILE_SIZE),GREEN,TILE_SIZE,0);
//             }
//             else if (root->map[my_y][my_x] == PLAYER)
//             {
//                 root->player->player_y = my_y;
//                 root->player->player_x = my_x;
//                 draw_squar(root, (my_y * TILE_SIZE), (my_x * TILE_SIZE),GREEN,TILE_SIZE,0);
//             }
//             my_x++;
//         }
//         my_y++;
//     }
//     // render_player(root);
//     // draw_circle(root,(root->player->player_y*TILE_SIZE)+20,(root->player->player_x*TILE_SIZE)+20,BLACK,5);
//     draw_line(root,(root->player->player_y)*40+20, (root->player->player_x)*40+20,(root->player->player_y*40) + (cos(root->player->rotationAngle))*40,(root->player->player_x *40) + (sin(root->player->rotationAngle))*40, BLACK);
// }