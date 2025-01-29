/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:34:35 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/29 14:56:29 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
void move_up(t_root *root)
{
    float angle = root->player->rotationAngle; // Don't modify this value
    float movestep = root->player->walkDir * root->player->walkSpeed * 0.2;
    float new_y = *root->player->player_y + sin(angle) * movestep;
    float new_x = *root->player->player_x + cos(angle) * movestep;
    
    if (!root || !root->player || !root->player->player_x || !root->player->player_y)
        return;
    if (!maphaswallat(root, new_y, new_x))
    {
        int current_tile_x = *root->player->player_x / TILE_SIZE;
        int current_tile_y = *root->player->player_y / TILE_SIZE;

        root->map[current_tile_y][current_tile_x] = FLOOR; // Clear old position
        *root->player->player_y = new_y;                  // Update Y
        *root->player->player_x = new_x;                  // Update X
        root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER; // Set new position
    }
}

void move_down(t_root *root)
{
    float angle = root->player->rotationAngle; // Current rotation angle
    float movestep = -1 * root->player->walkDir * root->player->walkSpeed * 0.2; // Inverted direction
    float new_y = *root->player->player_y + sin(angle) * movestep;
    float new_x = *root->player->player_x + cos(angle) * movestep;
    int current_tile_x = *root->player->player_x / TILE_SIZE;
    int current_tile_y = *root->player->player_y / TILE_SIZE;

    if (!root || !root->player || !root->player->player_x || !root->player->player_y)
        return;
    if (!maphaswallat(root, new_y, new_x))
    {
        root->map[current_tile_y][current_tile_x] = FLOOR; // Clear the old position
        *root->player->player_y = new_y;                  // Update Y
        *root->player->player_x = new_x;                  // Update X
        root->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] = PLAYER; // Set new position
    }
}

void move_right(t_root *root)
{
    if (!root || !root->player || !root->player->player_x || !root->player->player_y)
        return;
    root->player->rotationAngle -= root->player->turnDir * root->player->turnSpeed;
    root->player->turnDir = +1;

    float direction_line_y = *root->player->player_y + sin(root->player->rotationAngle) * 40; // 40 for TILE_SIZE length
    float direction_line_x = *root->player->player_x + cos(root->player->rotationAngle) * 40;
}

void move_left(t_root *root)
{
    root->player->rotationAngle += root->player->turnDir * root->player->turnSpeed;//
    float   movestep = root->player->walkDir * root->player->walkSpeed * 0.2;//
    
    int current_tile_y = *root->player->player_y / 40;
    int current_tile_x = *root->player->player_x / 40;

    if ((*root->player->player_x) / 40 == current_tile_x &&
        root->map[current_tile_y][current_tile_x - 1] == FLOOR)
    {
        root->map[current_tile_y][current_tile_x] = FLOOR;
        root->map[current_tile_y][*root->player->player_x / 40] = PLAYER;
        root->player->turnDir = -1;
    }
    float new_y = *root->player->player_y + sin(root->player->rotationAngle) * movestep;
    float new_x = *root->player->player_x + cos(root->player->rotationAngle) * movestep;
}

int move_player(int keycode, t_root *root)
{
    if (keycode == 53)
        exit(1);
    else if (keycode == 13 || keycode == 126)
        move_up(root);
    else if (keycode == 125 || keycode == 1)
        move_down(root);
    else if (keycode == 124 || keycode == 2)
        move_right(root);
    else if (keycode == 123 || keycode == 0)
        move_left(root);
    update(&root);
    return (0);
}