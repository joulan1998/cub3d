#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "includes/cub3d.h"
int check_wall(int y, int x, int map[MAP_HEIGHT][MAP_WIDTH])
{
    // int local_x = x*TILE_SIZE;
    // while ((local_x%TILE_SIZE))
        // local_x++;
    return((map[y][x] == WALL));
}

void draw_ray_up(void *mlx , void *win, int y ,int x,int color, int map[MAP_HEIGHT][MAP_WIDTH])
{
    int i = 1;
    int cor = y;

    // while (i < TILE_SIZE + 40)
    while (i)
    {
    //     printf("the result ot the YYYYYY piosition is %d\n",((y)/*/TILE_SIZE)- HALF_TILE_SIZE*/));
    //     printf("the result ot the XXXXXX piosition is %d\n",((x)/*/TILE_SIZE)- HALF_TILE_SIZE*/));
    //     printf("the result ot the plaeyr piosition is %c\n",map[(y/TILE_SIZE)- HALF_TILE_SIZE][(x/TILE_SIZE)- HALF_TILE_SIZE]);
    //     exit(1);

        if (!(cor%TILE_SIZE) && check_wall(cor/TILE_SIZE, x/TILE_SIZE,map))
        {
            // printf("the result ot the x piosition is %d\n",x/TILE_SIZE);
            // exit(9);
            return;
        }
        // if((y%TILE_SIZE) == 0 && map[y/TILE_SIZE][x/TILE_SIZE]== WALL)
        mlx_pixel_put(mlx, win,x,y-i, color);
        cor--;
        i++;
    }

}
void draw_player(void *mlx , void *win, int y ,int x,int color,int size)
{
    int my_y = y;
    int my_x = x;
    while(y < (my_y+size))
    {
        x = my_x;
        while (x < (my_x+size))
        {
            mlx_pixel_put(mlx, win,x++,y, color);
            x++;
        }
        y++;
    }
}

void draw_squar(void *mlx , void *win, int y ,int x,int color,int size, int exist)
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
                // if (exist==1 && ((y) == (HALF_TILE_SIZE*40)) && ((x) == (HALF_TILE_SIZE*40)))
                // {
                //     // draw_player(mlx, win, y,x,BLACK,20);
                //     // puts("success");
                //     // printf("the result of y is [%d]\n",y);
                //     // printf("the result of x is [%d]\n",x);
                //     // mlx_pixel_put(mlx, win,y,x, BLACK);
                //     // if (exist==1 && ((y/2) == (HALF_TILE_SIZE*40)) && ((x/2) == (HALF_TILE_SIZE*40)))
                //         // draw_player(mlx, win, (y), (x),BLUE,5);
                //     // draw_squar(mlx, win, (y+20), (x+20),BLACK,5,0);
                //     x++;
                //     // // continue;
                // }
                else
                    mlx_pixel_put(mlx, win,x++,y, color);
                    // printf("%d",x);
            }
            y++;
        }
}
char **reading_map(int fd)
{
    char *buffer;
    char *total;
    int readen;

    buffer = malloc(sizeof(char ) * 10);
    total = malloc(sizeof(char *));
    readen = read(fd, buffer, 10);
    while (readen > 0)
    {
        total = ft_strjoin(total,buffer);
        // if (total)
        //     free(buffer);
        readen =  read(fd, buffer,10);
    }
    // puts(total);
    puts("*********");
    return(ft_split(total, '\n'));
}

// void initialize_data(t_cub *data,char *map)
// {
//     data->map_height = count_lines(map);
//     data->map_width = ft_strlen(map[data->map_height]);
//     data-> = ft_strlen(map[data->map_height]);
//     data->map_width = ft_strlen(map[data->map_height]);


// }

int main()
{
    int player_x;
    int player_y;
    int my_y= 0;
    int my_x= 0;
    // char **map;
    int i = 0;
    int fd;
    void *mlx;
    void *win;
    int map[7][9] = {
        {1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,1},
        {1,0,0,0,0,0,2,0,1},
        {1,1,1,1,1,1,1,1,1},
    };
    // fd = open("./map.txt",O_RDONLY,0);
    // map = reading_map(fd);
    // initialise_data(&data, map);

    mlx = mlx_init();
    win = mlx_new_window(mlx, (MAP_WIDTH * TILE_SIZE),(MAP_HEIGHT * TILE_SIZE), "cub3D");
    while(my_y < MAP_HEIGHT)
    {
        my_x = 0;
        while (my_x < MAP_WIDTH)
        {
            // printf("the valur is %d\n",map[my_y][my_x]);
            // exit(8);
            if (map[my_y][my_x] == ONE)
                draw_squar(mlx,win, (my_y * TILE_SIZE), (my_x * TILE_SIZE),RED,TILE_SIZE,0);
            else if (map[my_y][my_x] == ZERO)
                draw_squar(mlx, win, (my_y * TILE_SIZE),(my_x * TILE_SIZE),GREEN,TILE_SIZE,0);
            else if (map[my_y][my_x] == PLAYER)
            {
                player_x = my_x;
                player_y = my_y;
                draw_squar(mlx, win, (my_y * TILE_SIZE), (my_x * TILE_SIZE),GREEN,TILE_SIZE,1);
            }
            my_x++;
        }
        my_y++;
    }
    draw_player(mlx,win,(player_y * TILE_SIZE + HALF_TILE_SIZE),(player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,5);
    draw_ray_up(mlx,win,(player_y * TILE_SIZE + HALF_TILE_SIZE),(player_x * TILE_SIZE + HALF_TILE_SIZE),BLACK,map);
    // mlx_string_put( mlx, win, 70, 70, RED, "test printing" );
	mlx_loop(mlx);
    return(0);
}