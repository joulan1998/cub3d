#include "includes/cub3d.h"


void move_up(t_player *player)
{
    // puts("hjshdjhsjdhdhjs");
    // printf("tge result of player test is %s\n",player->map[1]);
    // printf("tge result of player test is %d\n",player->map[player->player_y][player->player_x]);
    // printf("tge result of player is %c\n",player->map[player->player_y][player->player_x]);
        // exit(3);
    if (player->map[player->player_y-1][player->player_x] == FLOOR)
    {
        // printf("tge result of player is %d\n",player->player_y);
        player->map[player->player_y][player->player_x] = PLAYER;
        player->map[player->player_y-1][player->player_x] = FLOOR;
        player->player_y -= 1;
        draw_squar(player->mlx, player->win, (player->player_y /** TILE_SIZE*/), (player->player_y * TILE_SIZE),GREEN,TILE_SIZE,1);
    }
    return;
        
}

int move_player(int keycode, t_player *player)
{
    // exit(18);
    if (keycode == 126)
    {
        puts("pupupuupupupupuppup");
        // exit(9);
        move_up(player);
        return 0 ;
        // (void )player;
    }
        exit(99);
    
    return (1);
}