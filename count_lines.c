#include "includes/cub3d.h"

int count_lines(char **map)
{
    int i  = 0;
    if (!*map)
        return(0);
    while (map[i])
        i++;
    return(i);
}