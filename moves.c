#include "includes/cub3d.h"


void move_up(t_player *player)
{
    if (player->map[player->player_y-1][player->player_x] == FLOOR)
    {
        // printf("tge result of player is %d\n",player->player_y);
        player->map[player->player_y][player->player_x] = FLOOR;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        player->player_y -= 1;
        player->map[player->player_y][player->player_x] = PLAYER;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,player->map);
    }
    return;
        
}
void move_down(t_player *player)
{
    if (player->map[player->player_y+1][player->player_x] == FLOOR)
    {
        // printf("tge result of player is %d\n",player->player_y);
        player->map[player->player_y][player->player_x] = FLOOR;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        player->player_y += 1;
        player->map[player->player_y][player->player_x] = PLAYER;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,player->map);
    }
    return;
        
}
void move_left(t_player *player)
{
    if (player->map[player->player_y][player->player_x-1] == FLOOR)
    {
        player->map[player->player_y][player->player_x] = FLOOR;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        player->player_x -= 1;
        player->map[player->player_y][player->player_x] = PLAYER;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,player->map);
    }
    return;
        
}
void move_right(t_player *player)
{
    if (player->map[player->player_y][player->player_x+1] == FLOOR)
    {
        player->map[player->player_y][player->player_x] = FLOOR;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        player->player_x += 1;
        player->map[player->player_y][player->player_x] = PLAYER;
        draw_squar(player->mlx, player->win, (player->player_y * TILE_SIZE), (player->player_x * TILE_SIZE),GREEN,TILE_SIZE,1);
        draw_ray_up(player->mlx,player->win,(player->player_y * TILE_SIZE + HALF_TILE_SIZE),(player->player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,player->map);
    }
    return;
        
}

int move_player(int keycode, t_player *player)
{

    if (keycode == 126)
        move_up(player);
    else if (keycode == 125)
        move_down(player);
    else if (keycode == 124)
        move_right(player);
    else if (keycode == 123)
        move_left(player);
    else if (keycode == 53)
        exit(1);
    return (1);
}