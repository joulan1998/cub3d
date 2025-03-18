# include "../headers/cub3d.h"

// int **map_handling(int map[MAP_HEIGHT][MAP_WIDTH])
// {
//     int i;
//     int j = 0;
//     int **result = malloc(sizeof(int **));
//     while (j < MAP_HEIGHT)
//     {
//         result[j] = malloc(sizeof(int *));
//         i = 0;
//         while (i < MAP_WIDTH)
//         {
//             result[j][i] = malloc(sizeof(int));
//             result[j][i] = map[j][i];
//             i++;
//         }
//         j++;
//     }
//     return (result);
// }