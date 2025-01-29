#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "includes/cub3d.h"
int check_wall(int y, int x, char **map)
{
    return((map[y][x] == WALL));
}

void draw_ray_up(t_root *root, int y ,int x,int color, char **map)
{
    int i = 0;
    int cor = y;

    while (1)
    {

        if (!(cor%TILE_SIZE) && check_wall((cor/TILE_SIZE)-1, x/TILE_SIZE,map))
            return;
        mlx_pixel_put(root->mlx, root->win,x,y-i, color);
        cor--;
        i++;
    }

}
void set_player(t_player *p)
{
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
    mlx_key_hook(root->win,move_player,root);
	mlx_loop(root->mlx);
    return(0);
}
