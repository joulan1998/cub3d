#include "../../headers/cub3d.h"

void free_params(t_params *params)
{
    if (!params)
        return;
    free(params->so_texture);
    free(params->no_texture);
    free(params->we_texture);
    free(params->ea_texture);
    free_strings(params->map);
    free(params);
}

void free_strings(char **strings)
{
    int i;

    if (!strings)
        return;
    i = 0;
    while (strings[i])
    {
        // printf("%d line was freed\n", i);
        free(strings[i]);
        i++;
    }
    free(strings);
}

