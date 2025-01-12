#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "includes/cub3d.h"

void draw_squar(void *mlx , void *win, int y ,int x,int color)
{
    int my_x = x;
    int my_y = y;
        while (y < (my_y + TILE_SIZE))
        {
            x = my_x;
            while (x < (my_x + TILE_SIZE))
            {
                if (!(y % TILE_SIZE))
                {
                    y++;
                    continue;
                }
                if (!(x % TILE_SIZE))
                {
                    x++;
                    continue;
                }
                mlx_pixel_put(mlx, win,x++,y, color);
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
        {1,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1},
    };
    // fd = open("./map.txt",O_RDONLY,0);
    // map = reading_map(fd);
    // initialise_data(&data, map);

    mlx = mlx_init();
    win = mlx_new_window(mlx, (MAP_WIDTH * TILE_SIZE),(MAP_HEIGHT * TILE_SIZE), "cub3D");
    while(my_y < 7)
    {
        my_x = 0;
        while (my_x < 9)
        {
            // printf("the valur is %d\n",map[my_y][my_x]);
            // exit(8);
            if (map[my_y][my_x] == ONE)
                draw_squar(mlx,win, (my_y * TILE_SIZE), (my_x * TILE_SIZE),RED);
            else if (map[my_y][my_x] == ZERO)
                draw_squar(mlx, win, (my_y * TILE_SIZE),(my_x * TILE_SIZE),GREEN);
            else
                draw_squar(mlx, win, (my_y * TILE_SIZE), (my_x * TILE_SIZE),BLUE);
            my_x++;
        }
        my_y++;
    }
    // mlx_string_put( mlx, win, 70, 70, RED, "test printing" );
	mlx_loop(mlx);
    return(0);
}