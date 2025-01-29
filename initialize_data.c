/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/01/29 15:02:37 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
// static int prot  = 0;
void update(t_root **root)
{
    render_map(*root);
    render_player(*root);
    cast_allRays(*root);
    render_dir(*root);
    mlx_put_image_to_window((*root)->mlx, (*root)->win, (*root)->mlx_img.img,0 ,0);
    // int i =0;
    // while ((*root)->map[i])
    // {
    //     puts((*root)->map[i++]);
    // }
    
    
}

void initialize_data(t_root *root, char ***map, t_player *player)
{
    if (!map || !*map || !player || !player) // Validate inputs
        return;
    root->player = player;
    root->mlx = mlx_init();
    root->map = malloc(sizeof(char **));
    root->map = *map;
    root->map_h = count_lines(*map);
    root->map_w = ft_strlen(root->map[0]);
    root->win_w = root->map_w * TILE_SIZE;
    root->win_h = root->map_h * TILE_SIZE;
    root->win = mlx_new_window(root->mlx, root->win_w,root->win_h, "cub3D");
    root->mlx_img.img = mlx_new_image(root->mlx,root->win_w, root->win_h);
    root->mlx_img.addr = mlx_get_data_addr(root->mlx_img.img, &root->mlx_img.bits_per_pixel, &root->mlx_img.line_length, &root->mlx_img.endian);
}
