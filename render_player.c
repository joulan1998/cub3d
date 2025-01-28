/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:38:46 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/24 20:45:05 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void render_player(t_root *root)
{
    // printf("the valure of playr_render y=%d and x=%d\n",root->player->player_y, root->player->player_x);
    draw_circle(root,  *(root->player->player_y), *(root->player->player_x) ,RED,4);
    // printf("the valure of player_render y=%d and x=%d\n",root->player->player_y, root->player->player_x);
    // draw_line(root,root->player->player_y * TILE_SIZE+ 20, 
    //     root->player->player_x * TILE_SIZE+ 20,
    //     (root->player->player_y*40) + (cos(root->player->rotationAngle))*40
    //     , (root->player->player_x *40) + (sin(root->player->rotationAngle))*40,
    //      BLACK);
}