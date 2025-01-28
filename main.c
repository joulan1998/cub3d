#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "includes/cub3d.h"
int check_wall(int y, int x, char **map)
{
    // int local_x = x*TILE_SIZE;
    // while ((local_x%TILE_SIZE))
        // local_x++;
    return((map[y][x] == WALL));
}

void draw_ray_up(t_root *root, int y ,int x,int color, char **map)
{
    int i = 0;
    int cor = y;

    while (1)
    {

        if (!(cor%TILE_SIZE) && check_wall((cor/TILE_SIZE)-1, x/TILE_SIZE,map))
        {
            // printf("the result ot the x piosition is %d\n",cor/TILE_SIZE);
            // exit(9);
            return;
        }
        // if((y%TILE_SIZE) == 0 && map[y/TILE_SIZE][x/TILE_SIZE]== WALL)
        mlx_pixel_put(root->mlx, root->win,x,y-i, color);
        cor--;
        i++;
    }

}
void set_player(t_player *p)
{
    // p = malloc(sizeof(t_player));
    p->player_x = (int *)malloc(sizeof(int));
    p->player_y = (int *)malloc(sizeof(int));
    if (!p || !p->player_x || !p->player_y)
    {
        puts("error allocation!");
        exit(1);
    }
    p->walkSpeed = 100;
    p->turnSpeed = 45 * (M_PI / 180);
    *p->player_x = 0;
    *p->player_x = 0;
    p->turnDir = 0;
    p->walkDir = 1;
    p->rotationAngle = -M_PI / 2;
}

int main()
{
    t_player *player;
    t_root *root;
    int i = 0;
    int fd;
    void *mlx;
    void *win;
    char **map;
    player = malloc(sizeof(t_player));
    if (!player)
        puts("allocation for payer error\n");
    root = malloc(sizeof(t_root));
    fd = open("./map.txt",O_RDONLY,0);
    map = reading_map(fd);
    set_player(player);
    initialize_data(root,&map,player);
    update(&root);
    // parsing(root);

    // player->rotationAngle = (M_PI / 2)* -1;
    // player->root = root;
    // player->map = map;
    // cast_allRays(player);
    // draw_line(mlx,win,0 ,0,800,800,BLACK);
    // draw_player(mlx,win,(player_y * TILE_SIZE + HALF_TILE_SIZE),(player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,5);
    // draw_ray_up(mlx,win,(player_y * TILE_SIZE + HALF_TILE_SIZE),(player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,map);
    // mlx_string_put( mlx, win, 70, 70, RED, "test printing" );
    mlx_key_hook(root->win,move_player,root);
	mlx_loop(root->mlx);
    return(0);
}






//there is an issue in drawing the player 