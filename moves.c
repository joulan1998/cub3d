#include "includes/cub3d.h"


void move_up(t_root *root)
{
    if (root->map[root->player->player_y-1][root->player->player_x] == FLOOR)
    {
        root->player->walkDir = +1;
        root->map[root->player->player_y][root->player->player_x] = FLOOR;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        root->player->player_y -= 1;
        root->map[root->player->player_y][root->player->player_x] = PLAYER;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        // draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),RED,player->map);
        draw_circle(root,(root->player->player_y*TILE_SIZE)+20,(root->player->player_x*TILE_SIZE)+20,BLACK,5);
        draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,(root->player->player_y*40) + (cos(root->player->rotationAngle))*40,(root->player->player_x *40) + (sin(root->player->rotationAngle))*40,BLACK);
        // cast_allRays(player);
    }
    return;
        
}

void move_down(t_root *root)
{
     if (root->map[root->player->player_y+1][root->player->player_x] == FLOOR)
    {
        root->player->walkDir = -1;
        root->map[root->player->player_y][root->player->player_x] = FLOOR;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        root->player->player_y += 1;
        root->map[root->player->player_y][root->player->player_x] = PLAYER;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        // draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),RED,player->map);
        draw_circle(root,(root->player->player_y*TILE_SIZE)+20,(root->player->player_x*TILE_SIZE)+20,BLACK,5);
        draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,(root->player->player_y*40) + (cos(root->player->rotationAngle))*40,(root->player->player_x *40) + (sin(root->player->rotationAngle))*40,BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,root->player->player_y + cos(root->player->rotationAngle * 40),root->player->player_y + sin(root->player->rotationAngle * 40),BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,100,100,BLUE);
        // cast_allRays(player);
    }
    return;
}
void move_left(t_root *root)
{
    if (root->map[root->player->player_y][root->player->player_x-1] == FLOOR)
    {
        root->player->turnDir = -1;
        root->map[root->player->player_y][root->player->player_x] = FLOOR;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        root->player->player_x -= 1;
        root->map[root->player->player_y][root->player->player_x] = PLAYER;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        // draw_ray_up(root, (root->player->player_y * TILE_SIZE + HALF_TILE_SIZE),(root->player->player_x * TILE_SIZE + HALF_TILE_SIZE),RED,root->map);
        draw_circle(root,(root->player->player_y*TILE_SIZE)+20,(root->player->player_x*TILE_SIZE)+20,BLACK,5);
        draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,(root->player->player_y*40) + (cos(root->player->rotationAngle))*40,(root->player->player_x *40) + (sin(root->player->rotationAngle))*40,BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,root->player->player_y + cos(root->player->rotationAngle * 40),root->player->player_y + sin(root->player->rotationAngle * 40),BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,100,100,BLUE);
        // cast_allRays(root->player);
    }
    return;
        
}
void move_right(t_root *root)
{
     if (root->map[root->player->player_y][root->player->player_x+1] == FLOOR)
    {
        root->player->turnDir = +1;
        root->map[root->player->player_y][root->player->player_x] = FLOOR;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        root->player->player_x += 1;
        root->map[root->player->player_y][root->player->player_x] = PLAYER;
        draw_squar(root, (root->player->player_y * TILE_SIZE), (root->player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        // draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),RED,player->map);
        draw_circle(root,(root->player->player_y*TILE_SIZE)+20,(root->player->player_x*TILE_SIZE)+20,BLACK,5);
        draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,(root->player->player_y*40) + (cos(root->player->rotationAngle))*40,(root->player->player_x *40) + (sin(root->player->rotationAngle))*40,BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,root->player->player_y + cos(root->player->rotationAngle * 40),root->player->player_y + sin(root->player->rotationAngle * 40),BLACK);
        // draw_line(root,root->player->player_y * TILE_SIZE+ 20,root->player->player_x * TILE_SIZE+ 20,100,100,BLUE);
        // cast_allRays(player);
    }
    return;
        
}

int move_player(int keycode, t_root *root)
{

    if (keycode == 126)
        move_up(root);
    else if (keycode == 125)
        move_down(root);
    else if (keycode == 124)
        move_right(root);
    else if (keycode == 123)
        move_left(root);
    else if (keycode == 53)
        exit(1);
    return (1);
}