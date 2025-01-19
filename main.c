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
// void draw_player(void *mlx , void *win, int y ,int x,int color,int size)
// {
//     int my_y = y;
//     int my_x = x;
//     while(y < (my_y+size))
//     {
//         x = my_x;
//         while (x < (my_x+size))
//         {
//             mlx_pixel_put(mlx, win,x++,y, color);
//             x++;
//         }
//         y++;
//     }
// }

int main()
{
    t_player *player;
    t_root *root;
    int player_x;
    int player_y;
    int my_y= 0;
    int my_x= 0;
    int i = 0;
    int fd;
    void *mlx;
    void *win;
    char **map;
    player = malloc(sizeof(t_player *));

    fd = open("./map.txt",O_RDONLY,0);
    map = reading_map(fd);
    initialize_data(&root,&map,&player);
    parsing(root);

    player->rotationAngle = M_PI / 2;
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