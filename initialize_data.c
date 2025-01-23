/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/23 16:45:30 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void initialize_data(t_root *root, char ***map, t_player **player)
{
    if (!map || !*map || !player || !*player) // Validate inputs
        return;
    // (*root)->mlx = malloc(sizeof(void *) * 1);
    // if (!(*root)->mlx)
    //     puts("mlx init error");
    // (*root).win = malloc(1 *5);
    root->mlx = mlx_init();
    // exit(9);
    // if (!root)
    // {
    //     perror("Failed to allocate memory for root");
    //     return;
    // }
    root->map = *map;
    root->map_h = count_lines(*map);
    root->map_w = ft_strlen(root->map[0]);
    // if (!root->mlx)
    // {
    //     perror("Failed to initialize mlx");
    //     free(root);
    //     root = NULL;
    //     return;
    // }
    root->win_w = root->map_w * TILE_SIZE;
    root->win_h = root->map_h * TILE_SIZE;
    root->win = mlx_new_window(root->mlx, root->win_w/* (*root)->map_w * TILE_SIZE*/,root->win_h /*(*root)->map_h * TILE_SIZE*/, "cub3D");
    // if (!(*root)->win)
    // {
    //     perror("Failed to create a new window");
    //     free(*root);
    //     *root = NULL;
    //     return;
    // }
    root->player = *player;
}


// void initialize_data(t_root **root,char ***map)
// {
//     *root = malloc(sizeof(t_root *));

//     (*root)->map = malloc(sizeof(char *));
//     (*root)->map = *map;
//     (*root)->map_h = count_lines(*map);
//     (*root)->map_w = ft_strlen(**map);
//     (*root)->mlx = mlx_init();
//     (*root)->win = mlx_new_window((*root)->mlx,(*root)->map_w * TILE_SIZE,(*root)->map_h * TILE_SIZE, "cub3D");
//     int u = 0;
//     while((*root)->map[u])
//     {
//         puts((*root)->map[u]);
//         u++;
//     }
//     exit(0);
// }